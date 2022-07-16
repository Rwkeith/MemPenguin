#include "ProcessWindow.h"

MainInterface* ProcessWindow::mainInterface;

extern System mySystem;

// // Make the UI compact because there are so many fields
// static void PushStyleCompact()
// {
//     ImGuiStyle& style = ImGui::GetStyle();
//     ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
//     ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
// }

// static void PopStyleCompact()
// {
//     ImGui::PopStyleVar(2);
// }

ProcessWindow::ProcessWindow()
{
    AutoScroll = true;
    //Clear();
}

ProcessWindow::~ProcessWindow()
{
}

void ProcessWindow::Draw(bool &pOpen)
{
        if (!ImGui::Begin("Process Window", &pOpen))
        {
            ImGui::End();
            return;
        }
        
        // if refresh, disable button, update process list in system class, display process list.
        static bool refresh;
        if (refresh)
        {
            printf("User hit refresh\n");
            refresh = false;
            mySystem.ThreadUpdateProcs();
            if (mySystem.updatedProcList)
            {
                refresh = ImGui::Button("Refresh");
            }
        }
        else if (!refresh && !mySystem.updatedProcList)
        {
            ImGui::BeginDisabled();
            ImGui::Button("Refresh");
            ImGui::EndDisabled();
        }
        else
        {
            refresh = ImGui::Button("Refresh");
        }

        ImGui::SameLine();
        static int selectedRow = -1;
        static bool attach;
        if (!mySystem.isAttached && selectedRow != -1)
        {

            attach = ImGui::Button("Attach");
        }
        else
        {
            ImGui::BeginDisabled();
            ImGui::Button("Attach");
            ImGui::EndDisabled();
        }

        if (attach && selectedRow != -1)
        {
            attach = false;
            mySystem.procList[selectedRow].Attach();
        }
        

        ImGui::SameLine();
        static bool detach;
        
        if (!mySystem.isAttached)
        {
            ImGui::BeginDisabled();
            ImGui::Button("Detach");
            ImGui::EndDisabled();
        }
        else
        {
            detach = ImGui::Button("Detach");
        }

        if (detach && mySystem.isAttached)
        {
            detach = false;
            mySystem.attachedProcess.Detach();
        }
        ImGui::SameLine();
        filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (!refresh)
        {
            static ImGuiTableFlags flags1 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_ContextMenuInBody;

            // Context Menus: first example
            // [1.1] Right-click on the TableHeadersRow() line to open the default table context menu.
            // [1.2] Right-click in columns also open the default table context menu (if ImGuiTableFlags_ContextMenuInBody is set)
            const int COLUMNS_COUNT = 2;
            if (ImGui::BeginTable("table_context_menu", COLUMNS_COUNT, flags1))
            {
                ImGui::TableSetupColumn("PID");
                ImGui::TableSetupColumn("Process Name");
                //ImGui::TableSetupColumn("Three");

                // [1.1]] Right-click on the TableHeadersRow() line to open the default table context menu.
                ImGui::TableHeadersRow();
                //static bool selected[MAX_PROCESSES] = {};
                if (mySystem.procListMutex.try_lock())
                {
                    for (int row = 0; row < (int)mySystem.procList.size(); row++)
                    {
                        if (filter.IsActive())
                        {
                            const char* line_start = mySystem.procList[row].procName.c_str();
                            const char* line_end = mySystem.procList[row].procName.c_str() + mySystem.procList[row].procName.length();
                            if (filter.PassFilter(line_start, line_end))
                            {
                                ImGui::TableNextRow();
                                for (int column = 0; column < COLUMNS_COUNT; column++)
                                {
                                    ImGui::TableSetColumnIndex(column);
                                    if (column == 0)
                                    {
                                        char label[32];
                                        sprintf(label, "%d", mySystem.procList[row].pid);
                                        if (ImGui::Selectable(label, selectedRow == row, ImGuiSelectableFlags_SpanAllColumns)) selectedRow = row;
                                    }
                                    if (column == 1) ImGui::Text("%s", mySystem.procList[row].procName.c_str());
                                }
                            }
                        }
                        else
                        {
                            ImGui::TableNextRow();
                            for (int column = 0; column < COLUMNS_COUNT; column++)
                            {
                                ImGui::TableSetColumnIndex(column);
                                if (column == 0)
                                {
                                    char label[32];
                                    sprintf(label, "%d", mySystem.procList[row].pid);
                                    if (ImGui::Selectable(label, selectedRow == row, ImGuiSelectableFlags_SpanAllColumns)) selectedRow = row;
                                }
                                if (column == 1) ImGui::Text("%s", mySystem.procList[row].procName.c_str());
                            }
                        }
                    }
                    mySystem.procListMutex.unlock();
                }
                ImGui::EndTable();
            }
        }

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
}

void ProcessWindow::AddLog(const char* fmt, ...)
{
    int old_size = buffer.size();
    va_list args;
    va_start(args, fmt);
    buffer.appendfv(fmt, args);
    va_end(args);
    for (int new_size = buffer.size(); old_size < new_size; old_size++)
        if (buffer[old_size] == '\n')
            lineOffsets.push_back(old_size + 1);
}

void ProcessWindow::RegisterWindow(MainInterface* mainUI)
{
    mainInterface = mainUI;
}
