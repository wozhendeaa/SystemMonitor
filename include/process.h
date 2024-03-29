#ifndef PROCESS_H
#define PROCESS_H

#include <string>


/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    Process(){}
  Process(int pid_) ;
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

 private:
    std::string user;
    std::string cmd;
    long int ram;
    long int uptime;
    float cpu_utilization;
    int pid;
};

#endif