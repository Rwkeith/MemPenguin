#pragma once

#include <iostream>
#include <mutex>
#include "Process.h"
#include <thread>
#include <atomic>
#include <chrono>

//using namespace std::chrono_literals;

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
