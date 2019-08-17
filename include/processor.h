#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <fstream>
using std::ifstream;

//To calculate Linux CPU usage time subtract the idle CPU time from the total CPU time as follows:
//
//Total CPU time since boot = user+nice+system+idle+iowait+irq+softirq+steal
//
//Total CPU Idle time since boot = idle + iowait
//
//Total CPU usage time since boot = Total CPU time since boot - Total CPU Idle time since boot
//
//Total CPU percentage = Total CPU usage time since boot/Total CPU time since boot X 100
//
//If you use the formula on the example data above you should get a Linux CPU usage Percentage of 60%.
//
//Note: Guest and Guest_nice are already accounted in user and nice, hence they are not included in the total calculation
//
//For real time CPU usage, you will need to calculate the time between two intervals.

class Processor {
 public:
    Processor();
    float Utilization();
    void CopyVals();
    void SetVal(int i, int v);
    int GetVal(int i) const;
private:
    float TotalTimeSinceBoot();
    float IdleSinceBoot();
    float TotalUsageSinceBoot();
    float TotalPercentage();
    std::vector<int> prev_vals;
    std::vector<int> vals;
};

#endif