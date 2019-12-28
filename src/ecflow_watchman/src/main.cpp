#include <spdlog/spdlog.h>
#include <CLIUtils/CLI11.hpp>

#include <sstream>


int main(int argc, char **argv) {
    CLI::App app{"ecflow_watchman"};

    std::string rpc_target;

    CLI11_PARSE(app, argc, argv)

    return 0;
}