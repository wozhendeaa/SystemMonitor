#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>
#include "process.h"
#include "processor.h"
#include "Utility.h"

class System {
 public:
    Processor& AggregateCpu();
    int GetCoreCount() ;
    Processor& GetCpu(int i);
    std::vector<Process>& Processes();
    float MemoryUtilization();
    long UpTime();
    int TotalProcesses();
    int RunningProcesses();
    std::string Kernel();
    std::string OperatingSystem();

 private:
    //0 is the aggregate cpu info
    std::vector<Processor> cpus_ = {};
    std::vector<Process> processes_ = {};
    std::unordered_map<int, Process> process_map = {};


};



#endif