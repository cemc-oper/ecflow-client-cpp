#pragma once

#include "node.h"

namespace WorkflowModel {

struct NodeStatusRecord{
    std::string name_;
    std::string path_;
    std::string status_;
};

class Bunch: public Node {
public:
    Bunch();
    explicit Bunch(std::string name, NodeStatus status = NodeStatus::unknown);

    ~Bunch() override = default;

    std::shared_ptr<Node> findNode(std::string node_path);

    std::shared_ptr<Node> addNode(std::string node_path);

    std::shared_ptr<Node> addNodeStatus(const NodeStatusRecord &record);

};


} // namespace WorkflowModel