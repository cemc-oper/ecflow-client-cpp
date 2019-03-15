#include <ecflow_client/workflow_model/node_variable.h>

namespace WorkflowModel{

using json = nlohmann::json;

NodeVariable::NodeVariable(NodeVariableType type, const std::string &name, const std::string &value):
	name_{name},
	value_{value},
	type_{type}
{

}

json NodeVariable::toJson()
{
	json j;
	j["name"] = name_;
	j["value"] = value_;
	j["type"] = type_;
	return j;
}

} // namespace WorkflowModel