#pragma once

#include "node.h"
#include <nlohmann/json.hpp>

namespace WorkflowModel {

struct NodeStatusRecord {
    std::string path_;
    std::string status_;

    nlohmann::json toJson() const;
};

class Bunch : public Node {
public:
    Bunch();

    explicit Bunch(const std::string &name, NodeStatus status = NodeStatus::unknown);

    ~Bunch() override = default;

    std::shared_ptr<Node> findNode(const std::string &node_path);

    std::shared_ptr<Node> addNode(const std::string &node_path);

    std::shared_ptr<Node> addNodeStatus(const NodeStatusRecord &record);

};


} // namespace WorkflowModel