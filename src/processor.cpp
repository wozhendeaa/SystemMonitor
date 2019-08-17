#include "processor.h"
#include "linux_parser.h"
enum ProcessorNumber {
    USER = 0,
    NICE,
    SYSTEM,
    IDLE,
    IOWAIT,
    IRQ,
    SOFTIRQ,
    STEAL,
    GUEST,
    GUEST_NICE
};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    float utilization_val = TotalPercentage();
    return utilization_val;
}

float Processor::TotalTimeSinceBoot() {
    return vals[USER] + vals[NICE] + vals[SYSTEM] + vals[IDLE] +
            vals[IOWAIT] + vals[IRQ] + vals[SOFTIRQ] +
            vals[STEAL];
}

float Processor::IdleSinceBoot() {
    return vals[IDLE] + vals[IOWAIT];
}
float Processor::TotalUsageSinceBoot() {
    return TotalTimeSinceBoot() - IdleSinceBoot();
}
float Processor::TotalPercentage() {
    return TotalUsageSinceBoot() / TotalTimeSinceBoot();
}


