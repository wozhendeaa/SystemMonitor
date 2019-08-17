//
// Created by waynre on 8/17/19.
//
#include "Utility.h"


bool Utility::GetMatch(std::regex *reg, const std::string str, std::smatch &match) {
    bool rs = false;
    std::smatch rs_matches;
    if (std::regex_search(str, rs_matches, *reg) &&
        !rs_matches.empty() && rs_matches[1].matched) {
        match = rs_matches;
        rs = true;
    }
    return rs;
}
