#pragma once

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define PATH_LEN 200

/*
#define PROT_READ	0x1		 Page can be read.  
#define PROT_WRITE	0x2		 Page can be written.  
#define PROT_EXEC	0x4		 Page can be executed.  
#define PROT_NONE	0x0		 Page can not be accessed.  */

struct AddrSpaceEntry
{
    unsigned long startAddr;
    unsigned long endAddr;
    unsigned int size;
    char protection[10];
    unsigned int inode;
    char path[PATH_LEN];
};

class Process
{
private:
    int pid;
    char procName[50];
    std::vector<AddrSpaceEntry> addrSpace;

    int GetPid(bool wait);
public:
    Process(const char* inProcName, bool wait);
    ~Process();
    void UpdateAddrSpace();
    void PrintAddrSpace();
    unsigned long GetModuleBase(const char* moduleName);
    std::vector<AddrSpaceEntry> GetAddrSpace();
};
