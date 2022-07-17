#include "ProcessWindow.h"
#include "ConsoleWindow.h"
#include "MappingsWindow.h"

extern System mySystem;

MainInterface* ProcessWindow::mainInterface;
int ProcessWindow::selectedRow = -1;

ProcessWindow::ProcessWindow()
{
    AutoScroll = true;
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
        
        static bool showMappingsPressed;
        if (selectedRow != -1 && !mainInterface->showMappingWindow)
        {
            showMappingsPressed = ImGui::Button("Mappings");
        }
        else
        {
            ImGui::BeginDisabled();
            ImGui::Button("Mappings");
            ImGui::EndDisabled();
        }

        if (showMappingsPressed)
        {
            mainInterface->showMappingWindow = true;
        }
        
        ImGui::SameLine();
        filter.Draw("Filter", -50.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (!refresh)
        {
            static ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_ContextMenuInBody;

            const int COLUMNS_COUNT = 2;
            if (ImGui::BeginTable("table_context_menu", COLUMNS_COUNT, tableFlags))
            {
                ImGui::TableSetupColumn("PID");
                ImGui::TableSetupColumn("Process Name");

                ImGui::TableHeadersRow();
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
                                        if (mySystem.isAttached)
                                        {
                                            if (mySystem.attachedProcess.pid == mySystem.procList[row].pid)
                                            {
                                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                                                ImGui::Text("%s", label);
                                                ImGui::PopStyleColor();
                                            }
                                            else
                                                ImGui::Text("%s", label);
                                        }
                                        else
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
                                    if (mySystem.isAttached)
                                    {
                                        if (mySystem.attachedProcess.pid == mySystem.procList[row].pid)
                                        {
                                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                                            ImGui::Text("%s", label);
                                            ImGui::PopStyleColor();
                                        }
                                        else
                                            ImGui::Text("%s", label);
                                    }
                                    else
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
