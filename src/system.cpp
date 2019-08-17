#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace LinuxParser;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    std::ifstream is(kProcDirectory + kVersionFilename);
    std::regex reg {"Linux version (\\d*\\.\\d*\\.\\d*\\-\\d{2}\\-\\w*\\s)"};
    string kernel_name = "Not Found";
    string line;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch matches;
            if (std::regex_search(line, matches, reg) &&
               !matches.empty() && matches[1].matched) {
                kernel_name = matches[1];
                break;
            }
        }
    }
    return kernel_name;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    std::ifstream is( kOSPath);
    std::regex reg {"PRETTY_NAME=\"(.*)\""};
    string os_version = "Not Found";
    string line;
    if (is.is_open()) {
       while(getline(is, line)) {
           std::smatch matches;
           if (std::regex_search(line, matches, reg) &&
               !matches.empty() && matches[1].matched) {
               os_version = matches[1];
               break;
           }
       }
    }
    return os_version;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }