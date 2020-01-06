#include "watch.h"
#include "watch_all.h"
#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>
#include <future>


int main(int argc, char **argv) {
    CLI::App app{"ecflow_watchman"};

    CLI::App* watch_command = app.add_subcommand("watch", "watch an ecflow server");

    std::string owner;
    std::string repo;
    std::string ecflow_host;
    std::string ecflow_port;
    std::string redis_host;
    int redis_port = 6379;
    int max_count = -1;

    watch_command->add_option("--owner", owner, "owner")->required();
    watch_command->add_option("--repo", repo, "repo")->required();
    watch_command->add_option("--ecflow-host", ecflow_host, "ecflow host")->required();
    watch_command->add_option("--ecflow-port", ecflow_port, "ecflow port")->required();
    watch_command->add_option("--redis-host", redis_host, "redis host")->required();
    watch_command->add_option("--redis-port", redis_port, "redis port")->required();
    watch_command->add_option("--max-count", max_count, "max count, for test");

    CLI::App* watch_all_command = app.add_subcommand("watch-all", "watch several ecflow servers");

    std::string config_file_path;
    watch_all_command->add_option("--config-file", config_file_path, "config file path")->required();

    app.require_subcommand();
    CLI11_PARSE(app, argc, argv)

    if(watch_command->parsed()) {
        ecflow_watchman::WatchCommandOptions options{
                owner,
                repo,
                ecflow_host,
                ecflow_port,
                redis_host,
                redis_port,
                max_count
        };
        auto future = std::async(std::launch::async, ecflow_watchman::runWatchCommand, options);
        future.get();
    } else if(watch_all_command->parsed()){
        ecflow_watchman::WatchAllOptions options{
            config_file_path
        };
        ecflow_watchman::runWatchAllCommand(options);
    }

    return 0;
}