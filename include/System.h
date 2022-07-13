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
    std::atomic<bool> updateProcsThreadRunning;
    void UpdateProcessList();
public:
    std::mutex procListMutex;
    std::vector<Process> procList;
    std::atomic<bool> updatedProcList;
    System();
    ~System();
    void ThreadUpdateProcs();
    void PrintProcessList();
};
