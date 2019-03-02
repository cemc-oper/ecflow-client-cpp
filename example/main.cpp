#include <iostream>
#include <ClientInvoker.hpp>
#include <Defs.hpp>

struct NodeStatusRecord{
    std::string name_;
    std::string path_;
    std::string status_;
};

int main() {
    ClientInvoker invoker;
    invoker.set_host_port("10.40.143.18", "31071");
    auto sync_result = invoker.sync_local();

    auto defs = invoker.defs();

    std::vector<node_ptr> nodes;
    defs->get_all_nodes(nodes);

    std::vector<NodeStatusRecord> records;

    for(auto node: nodes) {
        NodeStatusRecord record;
        record.name_ = node->name();
        record.path_ = node->absNodePath();
        record.status_ = DState::toString(node->dstate());
        records.push_back(record);
    }


    return 0;
}