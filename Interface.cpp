#include "Interface.h"
#include "ConsoleWindow.h"
#include "ProcessWindow.h"
#include "MappingsWindow.h"


bool MainInterface::showConsole = true;
bool MainInterface::showProcWindow = false;
bool MainInterface::showMappingWindow = false;
MainInterface MainInterface::mainUI;
ConsoleWindow MainInterface::console;
ProcessWindow MainInterface::procWindow;
MappingsWindow MainInterface::mappingWindow;

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
    mappingWindow.RegisterWindow(&mainUI);
    if (showConsole) console.Draw(showConsole);
    if (showProcWindow) procWindow.Draw(showProcWindow);
    if (showMappingWindow) mappingWindow.Draw(showMappingWindow);
}