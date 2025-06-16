#pragma once
#include "metric_manager.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <atomic>
#include <sstream>

class MetricLogger {
public:
    MetricLogger(MetricManager& reg, const std::string& fileName, int intervalMs = 1000)
        : registry(reg), stop(false), interval(intervalMs), out(fileName) {}

    void start() {
        thread = std::thread([this] {
            while (!stop.load()) {
                logOnce();
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }
        });
    }

    void stopLogging() {
        stop.store(true);
        if (thread.joinable())
            thread.join();
    }

    ~MetricLogger() {
        stopLogging();
        if (out.is_open()) out.close();
    }

private:
    void logOnce() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto in_time_t = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::ostringstream line;
        line << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
             << "." << std::setfill('0') << std::setw(3) << ms.count();

        for (const auto& metric : registry.getMetrics()) {
            line << " " << metric->collectAndReset();
        }

        out << line.str() << std::endl;
    }

    MetricManager& registry;
    std::ofstream out;
    std::atomic<bool> stop;
    int interval;
    std::thread thread;
};
