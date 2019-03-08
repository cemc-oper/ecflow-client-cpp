#pragma once
#include "node_status.h"
#include "node_type.h"
#include "node_variable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

namespace WorkflowModel {

struct VariableList {

	nlohmann::json toJson() const;

	std::string path_;
	std::vector<NodeVariable> variable_list_;
	std::vector<NodeVariable> generated_variable_list_;
};

class WorkflowNode {
public:
	WorkflowNode() = default;

	void setName(const std::string &name) {
		name_ = name;
	}

	void setNodeStatus(NodeStatus status) {
		status_ = status;
	}

	void setNodeType(NodeType type) {
		node_type_ = type;
	}

	VariableList &variableList() {
		return variable_list_;
	}

	std::vector<VariableList> &inheritedVariableList() {
		return inherited_variable_list_;
	}

	nlohmann::json toJson() const;

private:
	std::string name_;
	NodeStatus status_ = NodeStatus::unknown;
	NodeType node_type_ = NodeType::Unknown;

	VariableList variable_list_;
	std::vector<VariableList> inherited_variable_list_;
};

} // namespace WorkflowModel