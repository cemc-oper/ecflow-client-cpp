#include <ecflow_client/ecflow_client.h>

#include <spdlog/spdlog.h>
#include <CLIUtils/CLI11.hpp>

#include <sstream>
#include <thread>

void runTask() {
    using namespace std::chrono_literals;
    while(true) {
        EcflowUtil::EcflowClient client{"10.40.143.18", "31071"};
        client.sync();
        auto records = client.statusRecords();
        spdlog::info("get nodes...{}", records.size());

        std::this_thread::sleep_for(10s);
    }
}


int main(int argc, char **argv) {
    CLI::App app{"ecflow_watchman"};

    std::string rpc_target;

    CLI11_PARSE(app, argc, argv)

    runTask();

    return 0;
}