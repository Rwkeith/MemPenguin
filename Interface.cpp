#include "Interface.h"
#include "ConsoleWindow.h"
#include "ProcessWindow.h"


bool MainInterface::showConsole = true;
bool MainInterface::showProcWindow = false;
MainInterface MainInterface::mainUI;
ConsoleWindow MainInterface::console;
ProcessWindow MainInterface::procWindow;

MainInterface::MainInterface()
{
    
}

MainInterface::~MainInterface()
{

}

void MainInterface::Update()
{
    console.RegisterWindow(&mainUI);
    procWindow.RegisterWindow(&mainUI);
    if (showConsole) console.Draw(showConsole);
    if (showProcWindow) procWindow.Draw(showProcWindow);
}