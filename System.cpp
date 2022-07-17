#include "System.h"

System::System()
{
    UpdateProcessList();
}

System::~System()
{
}

void System::ThreadUpdateProcs()
{
    if (!procsThreadRunning)
    {
        procsThreadRunning = true;
        updatedProcList = false;
        updateProcs = std::thread(&System::UpdateProcessList, this);
        updateProcs.detach();
        printf("Successfully created process update thread.\n");
        return;
    }
    
    printf("The process update thread is already running...\n");
}

void System::ThreadUpdateAddrSpace(int procID)
{
    if (!addrSpaceThreadRunning)
    {
        addrSpaceThreadRunning = true;
        updatedAddrSpace = false;
        updateAddrSpace = std::thread(&System::UpdateAddressSpace, this, procID);
        updateAddrSpace.detach();
        printf("Successfully created address space update thread.\n");
        return;
    }
    
    printf("The address space update thread is already running...\n");
}

void System::UpdateProcessList()
{
    printf("Updating process list...\n");
    
    int pid;
    char progName[1024] = {};
    char commandStr[] = "ps -A";
    char *lineBuffer = (char*)calloc(0x1000, 1);
    
    FILE * fp = popen(commandStr, "r");

    if (fp == NULL)
    {
        perror("Unable to open ps, or invalid argument\n");
        free(lineBuffer);
        procsThreadRunning = false;
        updatedProcList = true;
        return;
    }

    procListMutex.lock();
    procList.clear();
    while(fgets(lineBuffer, 0x1000, fp) != NULL)
    {
        sscanf(lineBuffer, "%i %*s %*s %s", &pid, progName);
        procList.push_back(Process(progName, pid));
        memset(progName, 0, 1024);
    }
    procListMutex.unlock();
    updatedProcList = true;
    int ret = pclose(fp);
    if (ret < 0)
    {
        perror("Unable to close fp for 'ps -A'\n");
    }
    
    free(lineBuffer);
    printf("Finished updating process list.\n");
    procsThreadRunning = false;
    return;
}

void System::UpdateAddressSpace(int row)
{
    addrSpaceMutex.lock();
    procList[row].UpdateAddrSpace();
    addrSpaceMutex.unlock();
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