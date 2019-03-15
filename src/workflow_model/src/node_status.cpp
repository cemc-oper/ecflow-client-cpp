#include <ecflow_client/workflow_model/node_status.h>

namespace WorkflowModel{
NodeStatus getNodeStatus(const std::string &status) {
    if (status == "suspended" || status == "sus") {
        return NodeStatus::suspended;
    }
    if (status == "complete" || status == "com") {
        return NodeStatus::complete;
    }
    if (status == "queued" || status == "que") {
        return NodeStatus::queued;
    }
    if (status == "submitted" || status == "sub") {
        return NodeStatus::submitted;
    }
    if (status == "active" || status == "act") {
        return NodeStatus::active;
    }
    if (status == "aborted" || status == "abo") {
        return NodeStatus::aborted;
    }
    if (status == "SHUTDOWN" || status == "shu") {
        return NodeStatus::shutdown;
    }
    if (status == "HALTED" || status == "hal") {
        return NodeStatus::halted;
    }
    if (status == "RUNNING") {
        return NodeStatus::running;
    }
    if (status == "unknown" || status == "unk") {
        return NodeStatus::unknown;
    }

    return NodeStatus::unknown;
}

std::string nodeStatusToString(NodeStatus status){
    if (status == NodeStatus::suspended) {
        return "suspended";
    }
    if (status == NodeStatus::complete) {
        return "complete";
    }
    if (status == NodeStatus::queued) {
        return "queued";
    }
    if (status == NodeStatus::submitted) {
        return "submitted";
    }
    if (status == NodeStatus::active) {
        return "active";
    }
    if (status == NodeStatus::aborted) {
        return "aborted";
    }
    if (status == NodeStatus::shutdown) {
        return "SHUTDOWN";
    }
    if (status == NodeStatus::halted) {
        return "HALTED" ;
    }
    if (status == NodeStatus::running) {
        return "RUNNING";
    }
    if (status == NodeStatus::unknown) {
        return "unknown";
    }

    return "unknown";
}
}
