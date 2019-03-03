#include "bunch.h"

#include <boost/algorithm/string.hpp>

namespace WorkflowModel{

Bunch::Bunch():
    Node{}{

}

Bunch::Bunch(const std::string &name, NodeStatus status):
    Node{name, status}
{

}

std::shared_ptr<Node> Bunch::findNode(const std::string &node_path) {
    if(node_path.length()==0){
        return std::shared_ptr<Node>();
    }

    if(node_path == "/"){
        return shared_from_this();
    }

    std::vector<std::string> tokens;
    boost::split(tokens, node_path, boost::is_any_of("/"));

    tokens.erase(tokens.begin());

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

std::shared_ptr<Node> Bunch::addNode(const std::string &node_path) {
    if(node_path == "/"){
        return shared_from_this();
    }

    std::shared_ptr<Node> node;

    std::vector<std::string> tokens;
    boost::split(tokens, node_path, boost::is_any_of("/"));
    tokens.erase(tokens.begin());

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
            t_node = std::make_shared<Node>(token);
            cur_node->addChild(t_node);
        }
        cur_node = t_node;
    }
    return cur_node;
}

std::shared_ptr<Node> Bunch::addNodeStatus(const NodeStatusRecord &record) {
    auto node = addNode(record.path_);
    node->setStatus(getNodeStatus(record.status_));
    return node;
}


} // namespace WorkflowModel
