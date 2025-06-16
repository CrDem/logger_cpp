#include "logger\metric.h"
#include "logger\metric_manager.h"
#include "logger\metric_logger.h"
#include <thread>
#include <random>

int main() {
    MetricManager manager;

    auto cpuMetric = std::make_shared<Metric<double>>("CPU");
    auto httpRps = std::make_shared<Metric<int>>("HTTP requests RPS");

    manager.registerMetric(cpuMetric);
    manager.registerMetric(httpRps);

    MetricLogger logger(manager, "metrics_output.txt");
    logger.start();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> cpuLoad(0.0, 4.0);
    std::uniform_int_distribution<> httpLoad(0, 100);

    for (int i = 0; i < 10; ++i) {
        cpuMetric->observe(cpuLoad(gen));
        httpRps->observe(httpLoad(gen));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    logger.stopLogging();

    return 0;
}
