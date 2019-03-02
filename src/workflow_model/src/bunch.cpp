#include "bunch.h"

#include <boost/algorithm/string.hpp>

namespace WorkflowModel{

Bunch::Bunch():
    Node{}{

}

Bunch::Bunch(std::string name, NodeStatus status):
    Node{name, status}
{

}

std::shared_ptr<Node> Bunch::findNode(std::string node_path) {
    if(node_path == "/"){
        return shared_from_this();
    }

    std::vector<std::string> tokens;
    boost::split(tokens, node_path, boost::is_any_of("/"));

    auto cur_node = shared_from_this();
    for(auto &token: tokens){
        std::shared_ptr<Node> t_node;
        for(auto &child: cur_node->children()){
            if(child->name() == token){
                t_node = child;
                break;
            }
        }
        if(!t_node){
            return nullptr;
        }
        cur_node = t_node;
    }
    return cur_node;
}

std::shared_ptr<Node> Bunch::addNode(std::string node_path) {
    return nullptr;
}

std::shared_ptr<Node> Bunch::addNodeStatus(const NodeStatusRecord &record) {
    return nullptr;
}


} // namespace WorkflowModel
