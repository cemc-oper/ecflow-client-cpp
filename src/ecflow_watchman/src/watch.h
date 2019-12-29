#pragma once
#include <string>

namespace ecflow_watchman {
struct WatchCommandOptions {
    std::string owner;
    std::string repo;
    std::string ecflow_host;
    std::string ecflow_port;
    std::string redis_host;
    int redis_port;
};

void runWatchCommand(const WatchCommandOptions &options);
} // namespace ecflow_watchman