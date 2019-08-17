//
// Created by waynre on 8/17/19.
//

#ifndef MONITOR_UTILITY_H
#define MONITOR_UTILITY_H
#include <regex>

class Utility {
public:
    static bool GetMatch(std::regex* reg,
                         const std::string str,
                           std::smatch& match);
};
#endif //MONITOR_UTILITY_H
