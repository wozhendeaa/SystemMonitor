#include <string>
#include <cmath>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {

    long hour = seconds / 3600;
    seconds %= 3600;
    long min = seconds / 60;
    seconds %= 60;
    long sec = seconds;
    string min_str = min < 10 ? "0" : "";
    min_str += std::to_string(min) + ":";

    string sec_str = sec < 10? "0" : "";
    sec_str += std::to_string(sec) ;

     return std::to_string(hour) + ":"
           + min_str + sec_str;
//return "12:23:33";
}