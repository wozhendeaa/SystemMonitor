#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <Utility.h>
#include <codecvt>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


vector<int> LinuxParser::Pids() {
    vector<int> pids;
    DIR* directory = opendir(kProcDirectory.c_str());
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

string LinuxParser::Uid(int pid) {
    string uid;

    std::stringstream path;
    path << kProcDirectory << "/" << pid << kStatusFilename;
    string p = path.str();
    auto& is = Utility::GetFileStream(p);
    string line;
    if (is.is_open()) {
        string reg {"Uid:\\s+(\\d*)"};
        std::smatch match;
        while (getline(is, line)) {
            string str = line;
            if (Utility::GetMatch(reg, str, match)) {
                uid = match[1].str();
                break;
            }
        }
    }
    is.close();

    return uid;
}

string LinuxParser::User(int pid) {
    string line;
    string user;
    string uid = Uid(pid);

    auto& is = Utility::GetFileStream(kPassword);
    if (is.is_open()) {
        std::stringstream ss;
        ss << "(.*):x:" << uid << ":" << uid << ":";
        std::smatch matches;
        while (getline(is, line)) {
            if (Utility::GetMatch(ss.str(), line, matches)) {
                user = matches[1].str();
                break;
            }
        }
    }
    is.close();

    return user;
}


long LinuxParser::UpTime() {
    auto& is = Utility::GetFileStream(kProcDirectory + kUptimeFilename);
    string line;
    long int result = 0;
    if (is.is_open()) {
        getline(is, line);
        int end = line.find(' ');
        auto start = std::atoll(line.substr(0, end).c_str());
        result = start;
    }
    is.close();
    return result;
}
