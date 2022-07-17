#pragma once

#include "imgui.h"
#include "System.h"

<<<<<<< HEAD
class ConsoleWindow;
class ProcessWindow;

class MainInterface
=======
<<<<<<< Updated upstream
class ConsoleWindow
=======
class ConsoleWindow;
class ProcessWindow;
class MappingsWindow;

class MainInterface
>>>>>>> Stashed changes
>>>>>>> 1985823 (Added mappings window.)
{
private:
    /* data */
public:
<<<<<<< HEAD
    static bool showConsole;
    static bool showProcWindow;
    static ConsoleWindow console;
    static ProcessWindow procWindow;
=======
<<<<<<< Updated upstream
    ConsoleWindow();
    ~ConsoleWindow();
    void ClearLog();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(const char* title, bool* p_open);
    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    static void MemPenguinOL();
    int TextEditCallback(ImGuiInputTextCallbackData* data);
=======
    static bool showConsole;
    static bool showProcWindow;
    static bool showMappingWindow;
    static ConsoleWindow console;
    static ProcessWindow procWindow;
    static MappingsWindow mappingWindow;
>>>>>>> 1985823 (Added mappings window.)
    MainInterface();
    ~MainInterface();
    static void Update();
    static MainInterface mainUI;
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
>>>>>>> 1985823 (Added mappings window.)
};
