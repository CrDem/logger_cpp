#pragma once
#include "metric_interface.h"
#include <string>
#include <atomic>
#include <sstream>

template<typename T>
class Metric : public IMetric {
public:
    Metric(const std::string& name) : name(name), value(0), count(0) {}

    void observe(T v) {
        value.fetch_add(v, std::memory_order_relaxed);
        count.fetch_add(1, std::memory_order_relaxed);
    }

    std::string collectAndReset() override {
        auto total = value.exchange(0);
        auto c = count.exchange(0);
        std::ostringstream oss;
        oss << "\"" << name << "\" ";
        if (c > 0) {
            if constexpr (std::is_floating_point<T>::value)
                oss << static_cast<double>(total) / c;
            else
                oss << total;
        } else {
            oss << 0;
        }
        return oss.str();
    }

private:
    std::string name;
    std::atomic<T> value;
    std::atomic<size_t> count;
};
