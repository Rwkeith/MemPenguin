#include "System.h"

System::System()
{
    UpdateProcessList();
    PrintProcessList();
}

System::~System()
{
}

int System::UpdateProcessList()
{
    updatingProcList = true;
    procList.clear();

    int pid;
    char progName[1024] = {};
    char commandStr[] = "ps -A";
    char *lineBuffer = (char*)calloc(0x1000, 1);
    
    FILE * fp = popen(commandStr, "r");

    if (fp == NULL)
    {
        printf("Unable to open ps, or invalid argument\n");
        return -1;
    }

    while(fgets(lineBuffer, 0x1000, fp) != NULL)
    {
        sscanf(lineBuffer, "%i %*s %*s %s", &pid, progName);
        procList.push_back(Process(progName, pid));
        memset(progName, 0, 1024);
    }
    
    pclose(fp);
    free(lineBuffer);
    updatingProcList = false;
    return 0;
}

void System::PrintProcessList()
{
    std::cout << "  PID  " << "  Name  " << std::endl;
    for (size_t i = 0; i < procList.size(); i++)
    {
        std::cout << procList[i].pid << "    " << procList[i].procName << std::endl;
    }
    std::cout << std::endl;
}