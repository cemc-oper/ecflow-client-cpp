#include <gtest/gtest.h>
#include <workflow_node.h>

#include <iostream>

namespace {
class WorkflowNodeTest : public ::testing::Test {
protected:
	WorkflowNodeTest() = default;
	~WorkflowNodeTest() = default;
	void SetUp() override {}
	void TearDown() override {}
};
using namespace WorkflowModel;
TEST_F(WorkflowNodeTest, MethodVariableListToJson) {
	WorkflowNodeVariables l;
	l.path_ = "/meso_post/00/initial";
	l.variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::Variable, "VAR1", "var1_value"},
		NodeVariable{NodeVariableType::Variable, "VAR2", "var2_value"},
	};

	l.generated_variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::GeneratedVariable, "GEN_VAR1", "gen_var1_value"},
		NodeVariable{NodeVariableType::GeneratedVariable, "GEN_VAR2", "gen_var2_value"},
		NodeVariable{NodeVariableType::GeneratedVariable, "GEN_VAR3", "gen_var3_value"},
	};

	auto j = l.toJson();

	EXPECT_EQ(j["path"], "/meso_post/00/initial");
	EXPECT_EQ(j["variable_list"].size(), 2);
	EXPECT_EQ(j["variable_list"][0]["name"], "VAR1");
	EXPECT_EQ(j["generated_variable_list"].size(), 3);
	EXPECT_EQ(j["generated_variable_list"][2]["name"], "GEN_VAR3");
}

TEST_F(WorkflowNodeTest, MethodToJson) {
	WorkflowNode node;
	node.setName("initial");
	node.setNodeStatus(NodeStatus::active);
	node.setNodeType(NodeType::Task);
	node.variableList().path_ = "/meso_post/00/initail";
	node.variableList().variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::Variable, "MAX_COUNT", "120"},
		NodeVariable{NodeVariableType::Variable, "WAITING_TIME", "60"},
	};

	node.variableList().generated_variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::GeneratedVariable, "ECF_NAME", "/meso_post/00/initail"},
	};

	WorkflowNodeVariables hh_var_list;
	hh_var_list.path_ = "/meso_post/00";
	hh_var_list.variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::Variable, "HH", "00"},
	};

	hh_var_list.generated_variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::GeneratedVariable, "ECF_NAME", "/meso_post/00"},
	};
	node.inheritedVariableList().push_back(hh_var_list);

	WorkflowNodeVariables suite_var_list;
	suite_var_list.path_ = "/meso_post";
	suite_var_list.variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::Variable, "SUITE", "meso_post"},
	};

	suite_var_list.generated_variable_list_ = std::vector<NodeVariable>{
		NodeVariable{NodeVariableType::GeneratedVariable, "ECF_NAME", "/meso_post"},
	};
	node.inheritedVariableList().push_back(suite_var_list);

	auto j = node.toJson();

	EXPECT_EQ(j["name"], "initial");
	EXPECT_EQ(j["variable_list"]["path"], "/meso_post/00/initail");
	EXPECT_EQ(j["variable_list"]["variable_list"].size(), 2);
	EXPECT_EQ(j["variable_list"]["variable_list"][0]["name"], "MAX_COUNT");
	EXPECT_EQ(j["inherited_variable_list"].size(), 2);
	EXPECT_EQ(j["inherited_variable_list"][1]["variable_list"][0]["name"], "SUITE");
}

}