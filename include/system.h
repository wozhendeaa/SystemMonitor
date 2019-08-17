#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include "process.h"
#include "processor.h"
class System {
 public:
    Processor& AggregateCpu();
    int GetCoreCount() ;
    Processor& GetCpu(int i);                   // TODO: See src/system.cpp
    std::vector<Process>& Processes();  // TODO: See src/system.cpp
    float MemoryUtilization();          // TODO: See src/system.cpp
    long UpTime();                      // TODO: See src/system.cpp
    int TotalProcesses();
    int RunningProcesses();
    std::string Kernel();
    std::string OperatingSystem();

  // TODO: Define any necessary private members
 private:
    //0 is the aggregate cpu info
    std::vector<Processor> cpus_ = {};
    std::vector<Process> processes_ = {};


};



#endif