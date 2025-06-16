#pragma once
#include "metric_interface.h"
#include <vector>
#include <memory>
#include <mutex>

class MetricManager {
public:
    void registerMetric(std::shared_ptr<IMetric> metric) {
        std::lock_guard<std::mutex> lock(mutex);
        metrics.push_back(metric);
    }

    std::vector<std::shared_ptr<IMetric>> getMetrics() {
        std::lock_guard<std::mutex> lock(mutex);
        return metrics;
    }

private:
    std::vector<std::shared_ptr<IMetric>> metrics;
    std::mutex mutex;
};