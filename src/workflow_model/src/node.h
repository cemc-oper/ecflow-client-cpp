#pragma once

#include "node_status.h"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace WorkflowModel {

class Node {
public:
    Node() = default;
    Node(const std::string &name,
        NodeStatus status = NodeStatus::unknown);

    void setParent(Node *parent){
        parent_ = parent;
    }

    Node *parent() const{
        return parent_;
    }

    void setName(const std::string &name){
        name_ = name;
    }

    std::string name() const {
        return name_;
    }

    void setStatus(NodeStatus status){
        status_ = status;
    }

    NodeStatus status(){
        return status_;
    }

    void addChild(Node &node);
    std::vector<Node> children(){
        return children_;
    }

    std::string nodePath() const;

    nlohmann::json toJson() const;
    std::string toJsonString() const;

private:
    std::string name_;
    Node *parent_ = nullptr;
    std::vector<Node> children_;
    NodeStatus status_ = NodeStatus::unknown;
};

} // namespace WorkflowModel
