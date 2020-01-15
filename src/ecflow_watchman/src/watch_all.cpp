#include "watch_all.h"
#include "collector.h"
#include "storer.h"

#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

#include <future>

using namespace std::chrono_literals;

namespace ecflow_watchman {

void runWatchAllCommand(const WatchAllOptions &options) {
    YAML::Node config = YAML::LoadFile(options.config_file_path);

    const auto redis_config = config["sink_config"];
    const auto redis_url = redis_config["url"].as<std::string>();

    int pos = redis_url.find(':');
    if(pos == std::string::npos) {
        spdlog::error("can't find : in redis_url: {}", redis_url);
        return;
    }

    const auto redis_host = redis_url.substr(0, pos);
    const auto redis_port_string = redis_url.substr(pos+1);
    int redis_port = std::stoi(redis_port_string);
    spdlog::info("creating redis storer: {}:{}", redis_host, redis_port_string);
    RedisStorer storer{
            redis_host,
            redis_port,
            "",
            0,
    };

    storer.create();

    const auto tasks = config["scrape_configs"];

    std::vector<std::future< void >> threads;

    for (const auto &task_config: tasks) {
        spdlog::info("load new job: {}", task_config["job_name"].as<std::string>());
        threads.push_back(std::async(std::launch::async, [&storer, task_config](){
            const auto owner = task_config["owner"].as<std::string>();
            const auto repo = task_config["repo"].as<std::string>();

            EcflowCollector collector{
                    owner,
                    repo,
                    task_config["host"].as<std::string>(),
                    task_config["port"].as<std::string>(),
            };

            const auto key = fmt::format("{}/{}/status", owner, repo);
            spdlog::info("[{owner}/{repo}] redis key: {key}",
                    fmt::arg("owner", owner),
                    fmt::arg("repo", repo),
                    fmt::arg("key", key));

            while (true) {
                std::this_thread::sleep_for(30s);
                auto value = collector.getStatusJsonString();

                spdlog::info("[{}/{}] save nodes...", owner, repo);
                storer.save(key, value);
                spdlog::info("[{}/{}] save nodes...done", owner, repo);
            }
        }));
    }
    for(auto &future: threads) {
        future.get();
    }
}

} // namespace ecflow_watchman