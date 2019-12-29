#include "watch_all.h"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

namespace ecflow_watchman {

void runWatchAllCommand(const WatchAllOptions &options) {
    YAML::Node config = YAML::LoadFile(options.config_file_path);

    const auto tasks = config["scrape_configs"];
    for (const auto &task_config: tasks) {
        fmt::print("load new job: {}\n", task_config["job_name"].as<std::string>());
    }
}

} // namespace ecflow_watchman