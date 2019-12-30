#include "watch.h"
#include "storer.h"

#include <ecflow_client/ecflow_client.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <date/date.h>

#include <thread>

using namespace std::chrono_literals;

namespace ecflow_watchman {

void runWatchCommand(const WatchCommandOptions &options) {
    RedisStorer storer{
        options.redis_host,
        options.redis_port,
        "",
        0,
    };

    storer.create();

    const auto key = fmt::format("{}/{}/status", options.owner, options.repo);

    while (true) {
        std::this_thread::sleep_for(10s);
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
        for (const auto &record: records) {
            nlohmann::json record_json;
            record_json["path"] = record.path_;
            record_json["status"] = record.status_;
            value_json["status_records"].push_back(record_json);
        }

        const auto value = value_json.dump();

        spdlog::info("save nodes...");
        storer.save(key, value);
        spdlog::info("save nodes...done");
    }
}
} // namespace ecflow_watchman