#include "watch.h"

#include <ecflow_client/ecflow_client.h>

#include <spdlog/spdlog.h>

#include <thread>

void runWatchCommand(const std::string &ecflow_host, const std::string &ecflow_port) {
    using namespace std::chrono_literals;
    while(true) {
        EcflowUtil::EcflowClient client{ecflow_host, ecflow_port};
        client.sync();
        auto records = client.statusRecords();
        spdlog::info("get nodes...{}", records.size());

        std::this_thread::sleep_for(10s);
    }
}


