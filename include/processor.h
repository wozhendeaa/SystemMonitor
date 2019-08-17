#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <fstream>
using std::ifstream;

class Processor {
 public:
    float Utilization();
 private:
    friend class System;
    float utilization_val {0.f};

};

#endif