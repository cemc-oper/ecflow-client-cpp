#include "ecflow_client.h"

#include <ClientInvoker.hpp>
#include <Defs.hpp>

namespace EcflowUtil{

using namespace WorkflowModel;

EcflowClient::EcflowClient(const std::string &host, const std::string &port):
    host_{host},
    port_{port}
{

}

std::vector<NodeStatusRecord> EcflowClient::collectStatus() {
    ClientInvoker invoker;
    invoker.set_host_port(host_, port_);
    auto sync_result = invoker.sync_local();

    auto defs = invoker.defs();

    std::vector<node_ptr> nodes;
    defs->get_all_nodes(nodes);

    std::vector<NodeStatusRecord> records;

    for(auto &node: nodes) {
        NodeStatusRecord record;
        record.path_ = node->absNodePath();
        record.status_ = DState::toString(node->dstate());
        records.push_back(record);
    }

    return records;
}

std::shared_ptr<WorkflowModel::Bunch> EcflowClient::collectBunch() {
    auto records = collectStatus();
    auto bunch = std::make_shared<Bunch>();
    for(auto &record: records){
        bunch->addNodeStatus(record);
    }
    return bunch;
}

void EcflowClient::sync() {
    bunch_ = collectBunch();
}
}