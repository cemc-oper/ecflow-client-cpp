#pragma once
#include <string>

namespace ecflow_watchman {

struct WatchAllOptions {
    std::string config_file_path;
};

void runWatchAllCommand(const WatchAllOptions &options);

} // namespace ecflow_watchman