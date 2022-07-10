#pragma once

#include "imgui.h"

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
    ConsoleWindow();
    ~ConsoleWindow();
    void ClearLog();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(const char* title, bool* p_open);
    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    static void MemPenguinOL();
    int TextEditCallback(ImGuiInputTextCallbackData* data);
};
