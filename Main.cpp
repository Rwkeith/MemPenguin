#include "Overlay.h"
#include "Process.h"
#include "Interface.h"

System mySystem;

int main(int, char**)
{
    //bool wait = true;
    //Process valheimProc("valheim.x86_64", wait);
    //valheimProc.GetModuleBase("libmonobdwgc-2.0.so");
    MainInterface mainUI;
    Overlay overlay;
    if (overlay.isInitialized)
    {
        overlay.Register((Overlay::UserOLFunc)mainUI.Update);
        overlay.Run();
    }
    return 0;
}