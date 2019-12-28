#include <spdlog/spdlog.h>
#include <CLIUtils/CLI11.hpp>

#include "watch.h"

int main(int argc, char **argv) {
    CLI::App app{"ecflow_watchman"};

    CLI::App* watch_command = app.add_subcommand("watch", "watch an ecflow server");
    app.require_subcommand();

    std::string ecflow_host;
    std::string ecflow_port;

    watch_command->add_option("--ecflow-host", ecflow_host, "ecflow host")->required();
    watch_command->add_option("--ecflow-port", ecflow_port, "ecflow port")->required();

    CLI11_PARSE(app, argc, argv)

    if(watch_command->parsed()) {
        runWatchCommand(ecflow_host, ecflow_port);
    }

    return 0;
}