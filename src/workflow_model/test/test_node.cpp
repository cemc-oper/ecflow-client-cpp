#include <gtest/gtest.h>
#include <node.h>

namespace {
class NodeTest: public ::testing::Test {
protected:
    NodeTest(){}
    virtual ~NodeTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(NodeTest, MethodConstructor){
    WorkflowModel::Node node;
    std::string node_path = "/grapes_meso_v4_3";
    node.setName(node_path);
    EXPECT_EQ(node.name(), node_path);
}
}