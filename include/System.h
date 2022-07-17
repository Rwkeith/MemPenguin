#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include "Process.h"

#define MAX_PROCESSES 1000

class System
{
private:
    std::thread updateProcs;
    std::thread updateAddrSpace;
    std::atomic<bool> procsThreadRunning;
    std::atomic<bool> addrSpaceThreadRunning;
    void UpdateProcessList();
    void UpdateAddressSpace(int procID);
public:
    std::mutex procListMutex;
    std::mutex addrSpaceMutex;
    std::vector<Process> procList;
    std::atomic<bool> updatedProcList;
    std::atomic<bool> updatedAddrSpace;
    std::atomic<bool> isAttached;
    Process attachedProcess;
    System();
    ~System();
    void ThreadUpdateProcs();
    void ThreadUpdateAddrSpace(int procID);
    void PrintProcessList();
};
