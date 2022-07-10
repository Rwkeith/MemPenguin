#include "Overlay.h"
#include "Process.h"
#include "Interface.h"

int main(int, char**)
{
    //bool wait = true;
    //Process valheimProc("valheim.x86_64", wait);
    //valheimProc.GetModuleBase("libmonobdwgc-2.0.so");
    Overlay overlay;
    if (overlay.isInitialized)
    {
        overlay.Register((Overlay::UserOLFunc)ConsoleWindow::MemPenguinOL);
        overlay.Run();
    }
    return 0;
}