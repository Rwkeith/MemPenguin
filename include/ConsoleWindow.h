#pragma once

#include "imgui.h"
#include "System.h"
#include "Interface.h"

class ConsoleWindow
{
private:
    char inputBuff[256];
    ImVector<char*> items;
    ImVector<const char*> commands;
    ImVector<char*> history;
    int historyPos;    // -1: new line, 0..history.Size-1 browsing history.
    ImGuiTextFilter filter;
    bool autoScroll;
    bool scrollToBottom;
public:
    static MainInterface* mainInterface;
    ConsoleWindow();
    ~ConsoleWindow();
    void RegisterWindow(MainInterface* mainUI);
    void ClearLog();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(bool &pOpen);
    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    int TextEditCallback(ImGuiInputTextCallbackData* data);
};