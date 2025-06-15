#pragma once
#include "metric_interface.h"
#include <string>
#include <atomic>

template<typename T>
class Metric : public IMetric {
public:
    Metric(const std::string& name) : name(name), value(0), count(0) {}

private:
    std::string name;
    std::atomic<T> value;
    std::atomic<size_t> count;
};