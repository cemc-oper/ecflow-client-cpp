#include <spdlog/spdlog.h>
#include <CLIUtils/CLI11.hpp>

#include "watch.h"

int main(int argc, char **argv) {
    CLI::App app{"ecflow_watchman"};

    CLI::App* watch_command = app.add_subcommand("watch", "watch an ecflow server");
    app.require_subcommand();

    std::string ecflow_host;
    std::string ecflow_port;
    std::string redis_host;
    int redis_port;

    watch_command->add_option("--ecflow-host", ecflow_host, "ecflow host")->required();
    watch_command->add_option("--ecflow-port", ecflow_port, "ecflow port")->required();
    watch_command->add_option("--redis-host", redis_host, "redis host")->required();
    watch_command->add_option("--redis-port", redis_port, "redis port")->required();

    CLI11_PARSE(app, argc, argv)

    if(watch_command->parsed()) {
        runWatchCommand(ecflow_host, ecflow_port, redis_host, redis_port);
    }

    return 0;
}