#pragma once

#include <bunch.h>

namespace EcflowUtil{

class EcflowClientPrivate;

class EcflowClient {
public:
    EcflowClient() = delete;
    EcflowClient(const std::string &host, const std::string &port);
    ~EcflowClient();

    void sync();

    std::shared_ptr<WorkflowModel::Bunch> bunch(){
        return bunch_;
    }

private:
    void collectBunch();
    std::vector<WorkflowModel::NodeStatusRecord> collectStatus();

    EcflowClientPrivate* p_;

    std::string host_;
    std::string port_;

    std::shared_ptr<WorkflowModel::Bunch> bunch_;
};

}

