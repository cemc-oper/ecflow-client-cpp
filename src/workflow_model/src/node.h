#pragma once

#include "node_status.h"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace WorkflowModel {

class Node: public std::enable_shared_from_this<Node>{
public:
    Node() = default;
    Node(const std::string &name,
        NodeStatus status = NodeStatus::unknown);

    virtual ~Node(){}

    void setParent(std::shared_ptr<Node> &&parent){
        parent_ = parent;
    }

    std::shared_ptr<Node> parent() const{
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

    void addChild(std::shared_ptr<Node> &node);

    std::vector<std::shared_ptr<Node>> children(){
        return children_;
    }

    std::string nodePath() const;

    nlohmann::json toJson() const;

    std::string toJsonString() const;

private:
    std::string name_;
    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> children_;
    NodeStatus status_ = NodeStatus::unknown;
};

} // namespace WorkflowModel
