#include "collector.h"

#include <ecflow_client/ecflow_client.h>
#include <nlohmann/json.hpp>
#include <date/date.h>
#include <spdlog/spdlog.h>

namespace ecflow_watchman{

EcflowCollector::EcflowCollector(
        std::string owner, std::string repo, std::string ecflow_host,
        std::string ecflow_port):
        owner_{std::move(owner)},
        repo_{std::move(repo)},
        ecflow_host_{std::move(ecflow_host)},
        ecflow_port_{std::move(ecflow_port)}{
}

std::string EcflowCollector::getStatusJsonString() {
    spdlog::info("[{}/{}] get nodes...", owner_, repo_);
    EcflowUtil::EcflowClient client{ecflow_host_, ecflow_port_};
    client.sync();
    auto records = client.statusRecords();
    auto collected_time = client.collectedTime();
    spdlog::info("[{}/{}] get nodes...done, got {} nodes", owner_, repo_, records.size());

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

    auto value = value_json.dump();
    return value;
}


}