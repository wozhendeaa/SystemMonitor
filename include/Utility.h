//
// Created by waynre on 8/17/19.
//

#ifndef MONITOR_UTILITY_H
#define MONITOR_UTILITY_H
#include <regex>
#include <fstream>
using std::ifstream;

class dirent;
class Utility {
    static ifstream stream;
public:
    static ifstream& GetFileStream(const std::string& path);
    static bool b_core_initialized;
    static bool GetMatch(const std::string &reg,
                         const std::string& str,
                         std::smatch& match);
    static dirent* GetFolderByName(
            const std::string& path,
            const std::string& name);
};
#endif //MONITOR_UTILITY_H
