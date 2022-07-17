#include "MappingsWindow.h"
#include "System.h"

extern System mySystem;

MainInterface* MappingsWindow::mainInterface;

MappingsWindow::MappingsWindow()
{
    AutoScroll = true;
}

void MappingsWindow::Draw(bool &pOpen)
{
        if (!ImGui::Begin("Mappings Window", &pOpen))
        {
            ImGui::End();
            return;
        }
        
        // if refresh, disable button, update process list in system class, display process list.
        static bool firstOpen = true;
        static int selectedRow = mainInterface->procWindow.selectedRow;
        if (firstOpen)
        {
            firstOpen = false;
            mySystem.updatedAddrSpace = false;
            mySystem.ThreadUpdateAddrSpace(selectedRow);
        }
                
        ImGui::SameLine();
        filter.Draw("Filter", -50.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (!firstOpen)
        {
            static ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_ContextMenuInBody;

            const int COLUMNS_COUNT = 3;
            if (ImGui::BeginTable("mappings_table", COLUMNS_COUNT, tableFlags))
            {
                ImGui::TableSetupColumn("start");
                ImGui::TableSetupColumn("end");
                //ImGui::TableSetupColumn("protection");
                ImGui::TableSetupColumn("path");

                ImGui::TableHeadersRow();

                // if (mySystem.addrSpaceMutex.lock())
                // {
                for (int row = 0; row < (int)mySystem.procList[selectedRow].addrSpace.size(); row++)
                {
                    if (filter.IsActive())
                    {
                        const char* line_start = mySystem.procList[selectedRow].addrSpace[row].strPath.c_str();
                        const char* line_end = mySystem.procList[selectedRow].addrSpace[row].path + mySystem.procList[selectedRow].addrSpace[row].strPath.length();
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
                            if (column == 0) ImGui::Text("%p", mySystem.procList[selectedRow].addrSpace[row].startAddr);
                            if (column == 1) ImGui::Text("%p", mySystem.procList[selectedRow].addrSpace[row].endAddr);
                            if (column == 2) ImGui::Text("%s", mySystem.procList[selectedRow].addrSpace[row].path);
                        }
                    }
                }
                mySystem.procListMutex.unlock();
            }
            ImGui::EndTable();
        }

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
}

void MappingsWindow::AddLog(const char* fmt, ...)
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

void MappingsWindow::RegisterWindow(MainInterface* mainUI)
{
    mainInterface = mainUI;
}