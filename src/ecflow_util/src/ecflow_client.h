#pragma once

#include <bunch.h>

namespace EcflowUtil{

class EcflowClient {
public:
    EcflowClient() = delete;
    EcflowClient(const std::string &host, const std::string &port);

    void sync();

    std::shared_ptr<WorkflowModel::Bunch> bunch(){
        return bunch_;
    }

private:
    std::shared_ptr<WorkflowModel::Bunch> collectBunch();
    std::vector<WorkflowModel::NodeStatusRecord> collectStatus();

    std::string host_;
    std::string port_;

    std::shared_ptr<WorkflowModel::Bunch> bunch_;
};

}

