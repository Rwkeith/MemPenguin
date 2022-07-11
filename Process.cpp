#include "Process.h"

Process::Process(const char* inProcName, int inPid)
{
    procName = inProcName;
    pid = inPid;
    UpdateAddrSpace();
}

Process::Process(const char* inProcName, bool wait)
{
    procName = inProcName;
    if (!GetPid(wait))
        return;
    
    UpdateAddrSpace();
}

Process::~Process()
{
}

int Process::GetPid(bool wait)
{
    char pidLine[1024];
    char commandStr[] = "pidof ";
    strcat(commandStr, procName.c_str());
    FILE * command = popen(commandStr, "r");

    if (command == NULL)
    {
        printf("Unable to open pidof, or invalid argument\n");
        return 0;
    }

    fgets(pidLine, 1024, command);
    pid = strtoul(pidLine, NULL, 10);
    pclose(command);
    if (wait && pid == 0)
    {
        printf("Waiting for %s to start...\n", procName.c_str());
        while (pid == 0)
        {
            sleep(3);
            command = popen(commandStr, "r");
            fgets(pidLine, 1024, command);
            pid = strtoul(pidLine, NULL, 10);
            pclose(command);
        }
    }
    else if (pid == 0)
    {
        printf("%s is not currently running...\n", procName.c_str());
        return pid;
    }
    printf("%s's process id is %i\n",procName.c_str(), pid);
    return pid;
}

unsigned long Process::GetModuleBase(const char* moduleName)
{
    printf("Searching for module base of %s\n", moduleName);

    UpdateAddrSpace();

    int elements = addrSpace.size();
    for (int i = 0; i < elements; i++)
    {
        char* ret = strstr(addrSpace[i].path, moduleName);
        if (ret)
        {
            printf("Found base address of %s: 0x%lx\n", moduleName, addrSpace[i].startAddr);
            return addrSpace[i].startAddr;
        }
    }

    printf("Failed to find module %s\n", moduleName);
    return 0;
}

void Process::UpdateAddrSpace()
{
    char *lineBuffer = (char*)calloc(0x1000, 1);
    AddrSpace addrSpaceEntry;
    
    addrSpace.clear();
    sprintf(lineBuffer, "/proc/%d/maps", pid);
    FILE *fp = fopen(lineBuffer, "r");
    if(fp == NULL)
    {
        printf("Error, unable to open %s.\n", lineBuffer);
        free(lineBuffer);
        return;
    }

    while(fgets(lineBuffer, 0x1000, fp) != NULL)
    {
        sscanf(lineBuffer, "%lx-%lx %s %*s %*s %i %s", &addrSpaceEntry.startAddr, &addrSpaceEntry.endAddr, addrSpaceEntry.protection, &addrSpaceEntry.inode, addrSpaceEntry.path);
        addrSpace.push_back(addrSpaceEntry);
        addrSpaceEntry = {};
    }

    free(lineBuffer);
}

std::vector<AddrSpace> Process::GetAddrSpace()
{
    UpdateAddrSpace();
    return addrSpace;
}

void Process::PrintAddrSpace()
{
    printf("Printing address space of %s\n", procName.c_str());

    UpdateAddrSpace();

    int elements = addrSpace.size();
    for (int i = 0; i < elements; i++)
    {
       printf("%lx-%lx %s %i %s\n", addrSpace[i].startAddr, addrSpace[i].endAddr, addrSpace[i].protection, addrSpace[i].inode, addrSpace[i].path);
    }
}