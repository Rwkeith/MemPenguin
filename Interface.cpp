#include "include/Interface.h"
#include "include/ConsoleWindow.h"
#include "include/ProcessWindow.h"
#include "include/Helpers.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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