#pragma once

#include "ecflow_client/workflow_model/bunch.h"
#include "ecflow_client/workflow_model/workflow_node.h"

namespace EcflowUtil {

class EcflowClientPrivate;

class EcflowClient {
public:
    EcflowClient() = delete;

    EcflowClient(const std::string &host, const std::string &port);

    ~EcflowClient();

    int sync();

    std::shared_ptr<WorkflowModel::Bunch> bunch();

    std::vector<WorkflowModel::NodeStatusRecord> statusRecords() {
        return status_records_;
    }

    std::shared_ptr<WorkflowModel::WorkflowNode> getWorkflowNode(const std::string &node_path);

    std::string errorMessage();

private:
    EcflowClientPrivate *p_;

    std::string host_;
    std::string port_;

    std::vector<WorkflowModel::NodeStatusRecord> status_records_;
};

}

