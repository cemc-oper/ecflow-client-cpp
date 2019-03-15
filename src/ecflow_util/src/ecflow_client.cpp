#include <ecflow_client/ecflow_client.h>

#include <ClientInvoker.hpp>
#include <Defs.hpp>
//#include <DState.hpp>

namespace EcflowUtil{

class EcflowClientPrivate{
public:
    EcflowClientPrivate(std::string host, std::string port):
		host_{ host }, port_{ port } {}

	int sync() {
        invoker_.set_host_port(host_, port_);
        auto sync_result = invoker_.sync_local();
        if(sync_result!=0){
            error_message_ = invoker_.errorMsg();
        }
        return sync_result;
    }

    std::vector<WorkflowModel::NodeStatusRecord> collectStatus(){
         defs_ = invoker_.defs();

        std::vector<node_ptr> nodes;
        defs_->get_all_nodes(nodes);

        std::vector<WorkflowModel::NodeStatusRecord> records;

        for(auto &node: nodes) {
            WorkflowModel::NodeStatusRecord record;
            record.path_ = node->absNodePath();
            record.status_ = DState::toString(node->dstate());
            records.push_back(record);
        }

        return records;
    }

    std::shared_ptr<WorkflowModel::WorkflowNode> getWorkflowNode(const std::string &node_path) {
        auto ecf_node = defs_->findAbsNode(node_path);
        if(ecf_node == nullptr){
            return std::shared_ptr<WorkflowModel::WorkflowNode>();
        }

        auto workflow_node = getWorkflowNodeOnly(ecf_node);

        auto parent_ecf_node = ecf_node->parent();
        while(parent_ecf_node){
            auto parent_workflow_node = getWorkflowNodeOnly(parent_ecf_node);
            workflow_node->inheritedVariableList().push_back(parent_workflow_node->variableList());
            parent_ecf_node = parent_ecf_node->parent();
        }


        return workflow_node;
    }

private:
    std::shared_ptr<WorkflowModel::WorkflowNode> getWorkflowNodeOnly(Node* ecf_node){
        if(ecf_node == nullptr){
            return std::shared_ptr<WorkflowModel::WorkflowNode>();
        }

        auto workflow_node = std::make_shared<WorkflowModel::WorkflowNode>();
        workflow_node->setName(ecf_node->name());
        workflow_node->setNodeStatus(WorkflowModel::getNodeStatus(DState::toString(ecf_node->dstate())));

        WorkflowModel::WorkflowNodeVariables variable_list;
        variable_list.path_ = ecf_node->absNodePath();

        auto variables = ecf_node->variables();
        for(auto &variable: variables){
            variable_list.variable_list_.emplace_back(
                WorkflowModel::NodeVariable{WorkflowModel::NodeVariableType::Variable, variable.name(), variable.theValue()});
        }

        std::vector<Variable> gen_variables;
        ecf_node->gen_variables(gen_variables);
        for(auto &variable: gen_variables){
            variable_list.generated_variable_list_.emplace_back(
                WorkflowModel::NodeVariable{WorkflowModel::NodeVariableType::GeneratedVariable, variable.name(), variable.theValue()});
        }

        workflow_node->variableList() = variable_list;

        return workflow_node;
    }

    std::shared_ptr<WorkflowModel::WorkflowNode> getWorkflowNodeOnly(node_ptr ecf_node) {
        return getWorkflowNodeOnly(ecf_node.get());
    }


    std::string host_;
    std::string port_;
    ClientInvoker invoker_;
    defs_ptr defs_;

    std::string error_message_;

    friend class EcflowClient;
};

EcflowClient::EcflowClient(const std::string &host, const std::string &port):
    host_{host},
    port_{port},
    p_{new EcflowClientPrivate{host, port}}
{

}

EcflowClient::~EcflowClient() {
    delete p_;
}

int EcflowClient::sync() {
    auto ret = p_->sync();
    if(ret != 0){
        return ret;
    }
    status_records_ = p_->collectStatus();
    bunch_ = std::make_shared<WorkflowModel::Bunch>();
    for(auto &record: status_records_){
        bunch_->addNodeStatus(record);
    }
    return 0;
}

std::shared_ptr<WorkflowModel::WorkflowNode> EcflowClient::getWorkflowNode(const std::string &node_path) {
    return p_->getWorkflowNode(node_path);
}

std::string EcflowClient::errorMessage() {
    return p_->error_message_;
}


} // namespace EcflowUtil