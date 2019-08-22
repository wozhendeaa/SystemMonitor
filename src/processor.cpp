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

void Processor::CopyVals() {
    prev_vals = vals;
}


Processor::Processor() {
    prev_vals.resize(10, 0);
    vals.resize(10, 0);
}

float Processor::Utilization() {
    float utilization_val = TotalPercentage();
    return utilization_val;
}

float Processor::TotalTimeSinceBoot() {
    return vals[USER] + vals[NICE] + vals[SYSTEM] + vals[IDLE] +
            vals[IOWAIT] + vals[IRQ] + vals[SOFTIRQ] +
            vals[STEAL] - prev_vals[USER] - prev_vals[NICE] - prev_vals[SYSTEM] - prev_vals[IDLE] -
                          prev_vals[IOWAIT] - prev_vals[IRQ] - prev_vals[SOFTIRQ] -
                          prev_vals[STEAL];
}

float Processor::IdleSinceBoot() {
    return vals[IDLE] + vals[IOWAIT] - prev_vals[IDLE] - prev_vals[IOWAIT];
}
float Processor::TotalUsageSinceBoot() {
    return TotalTimeSinceBoot() - IdleSinceBoot();
}
float Processor::TotalPercentage() {
    return TotalUsageSinceBoot() / TotalTimeSinceBoot();
}

void Processor::SetVal(int i, int v) {
    vals[i] = v;
}

int Processor::GetVal(int i) const {
    return vals[i];
}


