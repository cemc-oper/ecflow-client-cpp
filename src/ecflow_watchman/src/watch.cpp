#include "watch.h"

#include <ecflow_client/ecflow_client.h>

#include <spdlog/spdlog.h>

#include <thread>

void runWatchCommand(const WatchCommandOptions &options) {
    using namespace std::chrono_literals;
    while(true) {
        EcflowUtil::EcflowClient client{options.ecflow_host, options.ecflow_port};
        client.sync();
        auto records = client.statusRecords();
        spdlog::info("get nodes...{}", records.size());

        std::this_thread::sleep_for(10s);
    }
}


