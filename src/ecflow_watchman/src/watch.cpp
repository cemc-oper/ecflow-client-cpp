#include "watch.h"
#include "storer.h"
#include "collector.h"

#include <spdlog/spdlog.h>

#include <thread>

using namespace std::chrono_literals;

namespace ecflow_watchman {

void runWatchCommand(const WatchCommandOptions &options) {
    RedisStorer storer{
        options.redis_host,
        options.redis_port,
        "",
        0,
    };

    storer.create();

    EcflowCollector collector{
        options.owner,
        options.repo,
        options.ecflow_host,
        options.ecflow_port,
    };

    const auto key = fmt::format("{}/{}/status", options.owner, options.repo);

    while (true) {
        std::this_thread::sleep_for(10s);
        auto value = collector.getStatusJsonString();

        spdlog::info("save nodes...");
        storer.save(key, value);
        spdlog::info("save nodes...done");
    }
}
} // namespace ecflow_watchman