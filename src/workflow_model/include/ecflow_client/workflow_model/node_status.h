#pragma once

#include <string>

namespace WorkflowModel {

enum class NodeStatus{
    // node
    unknown = 0,
    suspended,
    complete,
    queued,
    submitted,
    active,
    aborted,

    // server
    shutdown,
    halted,
    running
};

NodeStatus getNodeStatus(const std::string &status);
std::string nodeStatusToString(NodeStatus status);

}

