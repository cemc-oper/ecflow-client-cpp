#pragma once
#include <string>

struct WatchAllOptions {
    std::string config_file_path;
};

void runWatchAllCommand(const WatchAllOptions& options);