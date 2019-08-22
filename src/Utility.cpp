//
// Created by waynre on 8/17/19.
//
#include <dirent.h>
#include "Utility.h"
bool Utility::b_core_initialized = false;
ifstream Utility::stream;

bool Utility::GetMatch(const std::string &reg,
                       const std::string& str,
                       std::smatch &match) {
    std::regex reg_exp {reg};
    bool result = std::regex_search(str, match, reg_exp);
    return result;
}

dirent *Utility::GetFolderByName(const std::string& path,
                                 const std::string& name) {
    DIR* dir = opendir(path.c_str());
    dirent* file = nullptr;
    while ((file = readdir(dir)) != nullptr) {
        if (file->d_type == DT_DIR && file->d_name == name) {
            break;
        }
    }
    return file;
}

ifstream &Utility::GetFileStream(const std::string& path) {
    stream.close();
    stream.open(path);
    return stream;
}

std::vector<int> Pids() {
    std::vector<int> pids;
    DIR* directory = opendir("");
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
            // Is every character of the name a digit?
            std::string filename(file->d_name);
            if (std::all_of(filename.begin(), filename.end(), isdigit)) {
                int pid = stoi(filename);
                pids.push_back(pid);
            }
        }
    }
    closedir(directory);
    return pids;
}

