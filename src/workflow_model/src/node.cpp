#include "node.h"

#include <boost/algorithm/string.hpp>

#include <sstream>
#include <iterator>

namespace WorkflowModel {

Node::Node(const std::string &name, WorkflowModel::NodeStatus status):
    name_{name},
    status_{status}
{

}

void Node::addChild(std::shared_ptr<Node> &node) {
    children_.push_back(node);
    node->setParent(shared_from_this());
}

std::string Node::nodePath() const {
    auto cur_node = shared_from_this();
    std::vector<std::string> node_list;
    while (cur_node) {
        node_list.push_back(cur_node->name());
        cur_node = cur_node->parent();
    }
    const char* const sep = "/";
    std::ostringstream imploded;
    std::copy(node_list.rbegin(), node_list.rend()-1,
              std::ostream_iterator<std::string>(imploded, sep));
    std::copy(node_list.rend()-1, node_list.rend(), std::ostream_iterator<std::string>(imploded));
    auto node_path = imploded.str();
    if (node_path.empty()){
        node_path = "/";
    }
    return node_path;
}

nlohmann::json Node::toJson() const {
    using json = nlohmann::json;
    json node_json;
    node_json["name"] = name_;
    node_json["status"] = status_;

    std::vector<json> children_json_array;
    for(auto &child: children_){
        auto child_json = child->toJson();
        children_json_array.push_back(child_json);
    }
    node_json["children"] = children_json_array;

    return node_json;
}

std::string Node::toJsonString() const {
    return toJson().dump();
}

}