#pragma once

#include "imgui.h"
#include "System.h"

class ConsoleWindow;
class ProcessWindow;

class MainInterface
{
private:
    /* data */
public:
    static bool showConsole;
    static bool showProcWindow;
    static ConsoleWindow console;
    static ProcessWindow procWindow;
    MainInterface();
    ~MainInterface();
    static void Update();
    static MainInterface mainUI;
};
