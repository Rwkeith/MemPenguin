#pragma once

#include "Interface.h"

class ProcessWindow
{
private:
    ImGuiTextBuffer buffer;
    ImGuiTextFilter filter;
    ImVector<int> lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool AutoScroll;  // Keep scrolling if already at the bottom.
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
public:
    static MainInterface* mainInterface;
    static int selectedRow;
    bool isVisible;
    ProcessWindow();
    ~ProcessWindow();
    void Draw(bool &pOpen);
    void RegisterWindow(MainInterface* mainUI);
};