#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <linux_parser.h>
#include <set>
#include <unordered_map>
#include <Utility.h>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

Process::Process(int pid_) : pid(pid_){
    cpu_utilization = CpuUtilization();
    cmd = Command();
}

int Process::Pid() {
    return pid;
}

float Process::CpuUtilization() {
    std::stringstream path;
    path << kProcDirectory << "/" << pid << kStatFilename;
    auto& is = Utility::GetFileStream(path.str());

    string line;
    std::unordered_map<int ,int> data = {
            {UTIME,0},
            {STIME,0},
            {CUTIME,0},
            {CSTIME,0},
            {STARTTIME,0}};

    if (is.is_open()) {
        getline(is, line);
        std::istringstream ss(line);
        string val;
        for (size_t i = 1, count = 0; count < data.size(); ++i) {
            ss >> val;
            if (data.find(i) != data.end()) {
                int val_int = std::atoi(val.c_str());
                data[i] = val_int;
                count++;
            }
        }
    }
    is.close();

    long int hertz = sysconf(_SC_CLK_TCK);
    float  total_time = data[UTIME] + data[STIME] +
                        data[CUTIME] + data[CSTIME];
    long long system_up_time = LinuxParser::UpTime();
    long int seconds = system_up_time  -  (data[STARTTIME] / hertz);
    float result =  100 * ((total_time / hertz) / seconds);
    return result;
}

string Process::Command() {
    if (!cmd.empty()) return cmd;
    std::stringstream path;
    path << kProcDirectory << "/" << pid << kCmdlineFilename;
    auto& is = Utility::GetFileStream(path.str());

    if (is.is_open()) {
        string reg {"VmSize:\\s+(\\d+)"};
        std::smatch match;
        getline(is, cmd);
    }
    is.close();

    return cmd;
}

string Process::Ram() {
    std::stringstream path;
    path << kProcDirectory << "/" << pid << kStatusFilename;
    auto& is = Utility::GetFileStream(path.str());
    string line;
    long long size;
    if (is.is_open()) {
        string reg {"VmSize:\\s+(\\d+)"};
        std::smatch match;
        while (getline(is, line)) {
            if (Utility::GetMatch(reg, line, match)) {
                size = std::strtoll(match[1].str().c_str(), nullptr, 10);
                break;
            }
        }
    }
    is.close();

    size /= 1000;
    ram = size;
    std::ostringstream ss;
    ss << size;
    return ss.str();
}

string Process::User() {
    if (user.empty()) {
        user = LinuxParser::User(pid);
    }
    return user;
}

long int Process::UpTime() {
    std::stringstream path;
    path << kProcDirectory << "/" << pid << kStatFilename;
    auto& is = Utility::GetFileStream(path.str());

    string line;
    long long time = 0;
    if (is.is_open()) {
        if(getline(is, line)) {
            std::istringstream ss(line);
            std::string val;
            for (int i = 0; i < STARTTIME; ++ i){
                ss >> val;
            }
            time = std::strtoll(val.c_str(), nullptr, 10);
        }
    }
    is.close();

    int hertz = sysconf(_SC_CLK_TCK);
    uptime = time / hertz;
    return uptime;
}

bool Process::operator<(const Process& a)  const{
    return cpu_utilization > a.cpu_utilization;
}