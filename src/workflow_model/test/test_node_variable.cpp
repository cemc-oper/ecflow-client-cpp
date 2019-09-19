#include <gtest/gtest.h>
#include "../include/ecflow_client/workflow_model/node_variable.h"

namespace {
class NodeVariableTest : public ::testing::Test {
protected:
    NodeVariableTest() {}

    virtual ~NodeVariableTest() {}

    void SetUp() override {}

    void TearDown() override {}
};

using namespace ::WorkflowModel;
TEST_F(NodeVariableTest, MethodConstruction
) {
auto node = std::make_shared<NodeVariable>(
    NodeVariableType::Variable, "ECF_DATE", "20190306");
EXPECT_EQ(node
->

type(), NodeVariableType::Variable

);
EXPECT_EQ(node
->

name(),

"ECF_DATE");
EXPECT_EQ(node
->

value(),

"20190306");
}
}