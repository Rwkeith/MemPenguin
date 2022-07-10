#pragma once

#include "Process.h"
#include <iostream>

class System
{
private:
    /* data */
public:
    std::vector<Process> procList;
    System();
    ~System();
    int UpdateProcessList();
    void PrintProcessList();
};
