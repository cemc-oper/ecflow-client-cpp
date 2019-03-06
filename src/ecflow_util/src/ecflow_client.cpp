#include "ecflow_client.h"

#include <ClientInvoker.hpp>
#include <Defs.hpp>

namespace EcflowUtil{

using namespace WorkflowModel;

class EcflowClientPrivate{
public:
    EcflowClientPrivate(const std::string &host, const std::string &port):
		host_{ host }, port_{ port } {}

    std::vector<NodeStatusRecord> collectStatus(){
        invoker_.set_host_port(host_, port_);
        auto sync_result = invoker_.sync_local();

        defs_ = invoker_.defs();

        std::vector<node_ptr> nodes;
        defs_->get_all_nodes(nodes);

        std::vector<NodeStatusRecord> records;

        for(auto &node: nodes) {
            NodeStatusRecord record;
            record.path_ = node->absNodePath();
            record.status_ = DState::toString(node->dstate());
            records.push_back(record);
        }

        return records;
    }

private:
    std::string host_;
    std::string port_;
    ClientInvoker invoker_;
    defs_ptr defs_;
    friend class EcflowClient;
};

EcflowClient::EcflowClient(const std::string &host, const std::string &port):
    host_{host},
    port_{port},
    p_{new EcflowClientPrivate{host, port}}
{

}

EcflowClient::~EcflowClient() {
    delete p_;
}

void EcflowClient::sync() {
    collectBunch();
}

std::vector<NodeStatusRecord> EcflowClient::collectStatus() {
    auto records = p_->collectStatus();
    return records;
}

void EcflowClient::collectBunch() {
    auto records = collectStatus();
    bunch_ = std::make_shared<Bunch>();
    for(auto &record: records){
        bunch_->addNodeStatus(record);
    }
}

} // namespace EcflowUtil