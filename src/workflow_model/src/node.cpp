#include "node.h"

#include <sstream>
#include <iterator>

namespace WorkflowModel {

Node::Node(const std::string &name, WorkflowModel::NodeStatus status):
    name_{name},
    status_{status}
{

}

void Node::addChild(Node &node) {
    children_.push_back(node);
    node.setParent(this);
}

std::string Node::nodePath() const {
    auto cur_node = this;
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

}