#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <regex>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "Utility.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace LinuxParser;


// TODO: Return the system's CPU
Processor& System::AggregateCpu() {
    return cpus_.front();
}

int System::GetCoreCount()  {

    ifstream stream(kProcDirectory + kStatFilename);
    auto& is = Utility::GetFileStream(kProcDirectory + kStatFilename);

    std::string line;
    int core_index = 0;
    if (stream.is_open()) {
        //Get one cpu per line
        while (getline(stream, line)) {
            std::string temp;
            std::istringstream ss(line);
            ss >> temp;
            if (temp.substr(0, 3) != "cpu") break;

            //get all numbers for each cpu
            //depending on the initialization status
            if (Utility::b_core_initialized) {
                int index = 0;
                cpus_[core_index].CopyVals();
                while (ss >> temp) {
                    int t = std::atoi(temp.c_str());
                    cpus_[core_index].SetVal(index++, t);
                }
            } else {
                Processor p;
                int index = 0;
                while (ss >> temp) {
                    int t = std::atoi(temp.c_str());
                    p.SetVal(index++, t);
                }
                cpus_.push_back(p);
            }
            core_index++;
        }
    }
    Utility::b_core_initialized = true;
    is.close();

    return cpus_.size() - 1;
}



vector<Process>& System::Processes() {
    auto &&pids = LinuxParser::Pids();
    for (int pid : pids) {
        if (process_map.find(pid) == process_map.end()) {
            Process p{pid};
            process_map[pid] = p;
            processes_.push_back(p);
        }
    }
    return processes_;
}

std::string System::Kernel() {
    auto& is = Utility::GetFileStream(kProcDirectory + kVersionFilename);
    string reg {"Linux version (\\d*\\.\\d*\\.\\d*\\-\\d{2}\\-\\w*\\s)"};
    string kernel_name = "Not Found";
    string line;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch rs_matches;
            if (Utility::GetMatch(reg, line, rs_matches)) {
                kernel_name = rs_matches[1];
            }
        }
    }
    is.close();

    return kernel_name;
}

float System::MemoryUtilization() {
    auto& is = Utility::GetFileStream(kProcDirectory + kMeminfoFilename);
    vector<float> vals;
    string line;
    if (is.is_open()) {
        string reg {".*:\\s*(\\d*)\\skB"};
        std::smatch rs_matches;
        const int VAL_COUNT = 4;
        for (int i = 0; i < VAL_COUNT; ++ i){
            getline(is, line);
            if (Utility::GetMatch(reg, line, rs_matches)) {
                float val = std::atof(rs_matches[1].str().c_str());
                vals.push_back(val);
            }
        }
    }
    float utilization = 0.0f;
    if (!vals.empty()) {
        float mem_total = vals[0];
        float mem_available = vals[2];

        float used = mem_total - mem_available;
        utilization = (used ) / mem_total;
    }
    is.close();

    return utilization;
}

std::string System::OperatingSystem() {
    auto& is = Utility::GetFileStream(kOSPath);
    string reg {"PRETTY_NAME=\"(.*)\""};
    string os_version = "Not Found";
    string line;
    if (is.is_open()) {
       while(getline(is, line)) {
           std::smatch rs_matches;
            if (Utility::GetMatch(reg, line, rs_matches)) {
                os_version = rs_matches[1].str();
            }
       }
    }
    is.close();

    return os_version;
}

int System::RunningProcesses() {
    auto& is = Utility::GetFileStream(kProcDirectory + kStatFilename);
    string reg {"procs_running\\s(\\d*)"};
    string line;
    int result = 0;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch matches;
            if (Utility::GetMatch(reg, line, matches)) {
                result = atoi(matches[1].str().c_str());
                break;
            }
        }
    }
    is.close();

    return result;
}

int System::TotalProcesses() {
    auto& is = Utility::GetFileStream(kProcDirectory + kStatFilename);

    string reg {"processes\\s(\\d*)"};
    string line;
    int result = 0;
    if (is.is_open()) {
        while (getline(is, line)) {
            std::smatch matches;
            if (Utility::GetMatch(reg, line, matches)) {
                result = atoi(matches[1].str().c_str());
                break;
            }
        }
    }
    is.close();
    return result;
}

long int System::UpTime() {
    return LinuxParser::UpTime();
}

Processor &System::GetCpu(int i) {
    return cpus_[i];
}

