#pragma once

#include "imgui.h"
#include "System.h"

class ConsoleWindow;
class ProcessWindow;
class MappingsWindow;

class MainInterface
{
private:
    /* data */
public:
    static bool showConsole;
    static bool showProcWindow;
    static bool showMappingWindow;
    static ConsoleWindow console;
    static ProcessWindow procWindow;
    static MappingsWindow mappingWindow;
    MainInterface();
    ~MainInterface();
    static void Update();
    static MainInterface mainUI;
};
