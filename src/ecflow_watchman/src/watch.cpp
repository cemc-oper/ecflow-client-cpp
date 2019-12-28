#include "watch.h"

#include <ecflow_client/ecflow_client.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <date/date.h>

#include <sw/redis++/redis++.h>

#include <thread>

void runWatchCommand(const WatchCommandOptions &options) {
    using namespace std::chrono_literals;
    using namespace sw::redis;

    ConnectionOptions connection_options;
    connection_options.host = options.redis_host;
    connection_options.port = options.redis_port;
//    connection_options.password = "";   // Optional. No password by default.
//    connection_options.db = 0;

    connection_options.socket_timeout = std::chrono::milliseconds(200);

    Redis redis_client(connection_options);

    const auto key = fmt::format("{}/{}/status", options.owner, options.repo);

    while(true) {
        EcflowUtil::EcflowClient client{options.ecflow_host, options.ecflow_port};
        client.sync();
        auto records = client.statusRecords();
        auto collected_time = client.collectedTime();
        spdlog::info("get nodes...{}", records.size());

        nlohmann::json value_json;
        value_json["collected_time"] = date::format(
                "%FT%TZ",
                std::chrono::time_point_cast<std::chrono::milliseconds>(collected_time));

        value_json["status_records"] = nlohmann::json::array();
        for(const auto& record: records) {
            nlohmann::json record_json;
            record_json["path"] = record.path_;
            record_json["status"] = record.status_;
            value_json["status_records"].push_back(record_json);
        }

        const auto value = value_json.dump();

        spdlog::info("save nodes...");
        redis_client.set(key, value);
        spdlog::info("save nodes...done");

        std::this_thread::sleep_for(10s);
    }
}


