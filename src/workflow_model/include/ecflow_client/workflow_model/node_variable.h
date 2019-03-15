#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace WorkflowModel {

enum class NodeVariableType{
    Variable = 0,
    GeneratedVariable = 1
};

class NodeVariable {
public:
	NodeVariable(NodeVariableType type, const std::string &name, const std::string &value);

	std::string name() {
		return name_;
	}

	std::string value() {
		return value_;
	}

	NodeVariableType type() {
		return type_;
	}

	nlohmann::json toJson();
    
private:
    std::string name_;
    std::string value_;
    NodeVariableType type_;
};

}
