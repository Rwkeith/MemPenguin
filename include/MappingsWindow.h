#pragma once

#include "Interface.h"
#include "ProcessWindow.h"

class MappingsWindow
{
    ImGuiTextBuffer buffer;
    ImGuiTextFilter filter;
    ImVector<int> lineOffsets;
    bool AutoScroll;
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
public:
    static MainInterface* mainInterface;
    bool isVisible;
    MappingsWindow();
    ~MappingsWindow() {};
    void Draw(bool &pOpen);
    void RegisterWindow(MainInterface* mainUI);
};