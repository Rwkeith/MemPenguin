#pragma once

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <limits.h>


/*
#define PROT_READ	0x1		 Page can be read.  
#define PROT_WRITE	0x2		 Page can be written.  
#define PROT_EXEC	0x4		 Page can be executed.  
#define PROT_NONE	0x0		 Page can not be accessed.  */

struct AddrSpace
{
    unsigned long startAddr;
    unsigned long endAddr;
    unsigned int size;
    char protection[10];
    unsigned int inode;
    char path[PATH_MAX];
    std::string strPath;
};

class Process
{
private:
    int GetPid(bool wait);
public:
    int pid;
    std::string procName;
    std::vector<AddrSpace> addrSpace;
    Process() {};
    Process(const char* inProcName, int inPid);
    Process(const char* inProcName, bool wait);
    Process(const Process& p1);
    ~Process();
    void UpdateAddrSpace();
    void PrintAddrSpace();
    unsigned long GetModuleBase(const char* moduleName);
    std::vector<AddrSpace> GetAddrSpace();
    int Attach();
    int Detach();
};
