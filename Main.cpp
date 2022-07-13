#include "Overlay.h"
#include "Process.h"
#include "Interface.h"

System mySystem;

int main(int, char**)
{
    MainInterface mainUI;
    Overlay overlay;
    if (overlay.isInitialized)
    {
        overlay.Register((Overlay::UserOLFunc)mainUI.Update);
        overlay.Run();
    }
    return 0;
}