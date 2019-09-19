#include <ecflow_client/workflow_model/workflow_node.h>

namespace WorkflowModel {
using json = nlohmann::json;

json WorkflowNodeVariables::toJson() const {
    json j;
    j["path"] = path_;

    std::vector<json> variable_list_json;
    for (auto variable : variable_list_) {
        variable_list_json.push_back(variable.toJson());
    }
    j["variable_list"] = variable_list_json;

    std::vector<json> generated_variable_list_json;
    for (auto variable : generated_variable_list_) {
        generated_variable_list_json.push_back(variable.toJson());
    }
    j["generated_variable_list"] = generated_variable_list_json;

    return j;
}

json WorkflowNode::toJson() const {
    json j;
    j["name"] = name_;
    j["status"] = status_;
    j["node_type"] = node_type_;
    j["variable_list"] = variable_list_.toJson();

    std::vector<json> inherited_variable_list_json;
    for (auto variable : inherited_variable_list_) {
        inherited_variable_list_json.push_back(variable.toJson());
    }
    j["inherited_variable_list"] = inherited_variable_list_json;

    return j;
}
}