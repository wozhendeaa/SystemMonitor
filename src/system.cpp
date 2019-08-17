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

// TODO: Return a container composed of the
//  system's processes
vector<Process>& System::Processes() {

    return processes_;
}

std::string System::Kernel() {
    std::ifstream is(kProcDirectory + kVersionFilename);
    std::regex reg {"Linux version (\\d*\\.\\d*\\.\\d*\\-\\d{2}\\-\\w*\\s)"};
    string kernel_name = "Not Found";
    string line;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch rs_matches;
            if (GetMatch(&reg, line, rs_matches)) {
                kernel_name = rs_matches[1];
            }
        }
    }
    return kernel_name;
}

float System::MemoryUtilization() {
    std::ifstream is(kProcDirectory + kMeminfoFilename);
    vector<float> vals;
    string line;
    if (is.is_open()) {
        std::regex reg {".*:\\s*(\\d*)\\skB"};
        std::smatch rs_matches;
        const int VAL_COUNT = 4;
        for (int i = 0; i < VAL_COUNT; ++ i){
            getline(is, line);
            if (GetMatch(&reg, line, rs_matches)) {
                float val = std::atof(rs_matches[1].str().c_str());
                vals.push_back(val);
            }
        }
    }
    float utilization = 0.0f;
    if (!vals.empty()) {
        float mem_total = vals[0];
        float mem_free = vals[1];
        float mem_buffers = vals[3];

        float used = mem_total - mem_free;
        utilization = (used + mem_buffers) / mem_total;
    }
    return utilization;
}

std::string System::OperatingSystem() {
    std::ifstream is( kOSPath);
    std::regex reg {"PRETTY_NAME=\"(.*)\""};
    string os_version = "Not Found";
    string line;
    if (is.is_open()) {
       while(getline(is, line)) {
           std::smatch rs_matches;
            if (GetMatch(&reg, line, rs_matches)) {
                os_version = rs_matches[1];
            }
       }
    }
    return os_version;
}

int System::RunningProcesses() {
    std::ifstream is(kProcDirectory + kStatFilename);
    std::regex reg {"procs_running\\s(\\d*)"};
    string line;
    int result = 0;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch matches;
            if (GetMatch(&reg, line, matches)) {
                result = atoi(matches[1].str().c_str());
                break;
            }
        }
    }
    return result;
}

int System::TotalProcesses() {
    std::ifstream is(kProcDirectory + kStatFilename);
    std::regex reg {"processes\\s(\\d*)"};
    string line;
    int result = 0;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch matches;
            if (GetMatch(&reg, line, matches)) {
                result = atoi(matches[1].str().c_str());
                break;
            }
        }
    }
    return result;
}

long int System::UpTime() {
    std::ifstream is(kProcDirectory + kUptimeFilename);
    string line;
    long int result = 0;
    if (is.is_open()) {
        getline(is, line);
        int end = line.find(' ');
        auto start = std::atoll(line.substr(0, end).c_str());
        auto now = std::atoll(line.substr(end + 1).c_str());
        result = now - start;
    }
    return result;
}

bool System::GetMatch(std::regex* reg,
                      std::string str,
                      std::smatch& matches) {
    bool rs = false;
    std::smatch rs_matches;
    if (std::regex_search(str, rs_matches, *reg) &&
        !rs_matches.empty() && rs_matches[1].matched) {
        matches = rs_matches;
        rs = true;
    }
    return rs;
}
