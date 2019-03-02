#include <gtest/gtest.h>
#include <node_status.h>

namespace {
class NodeStatusTest: public ::testing::Test {
protected:
    NodeStatusTest(){}
    virtual ~NodeStatusTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(NodeStatusTest, MethodGetNodeStatus){
    EXPECT_EQ(WorkflowModel::getNodeStatus("unknown"), WorkflowModel::NodeStatus::unknown)
    EXPECT_EQ(WorkflowModel::getNodeStatus("unk"), WorkflowModel::NodeStatus::unknown)
    EXPECT_EQ(WorkflowModel::getNodeStatus("suspended"), WorkflowModel::NodeStatus::suspended)
    EXPECT_EQ(WorkflowModel::getNodeStatus("sus"), WorkflowModel::NodeStatus::suspended)
    EXPECT_EQ(WorkflowModel::getNodeStatus("complete"), WorkflowModel::NodeStatus::complete)
    EXPECT_EQ(WorkflowModel::getNodeStatus("com"), WorkflowModel::NodeStatus::complete)
    EXPECT_EQ(WorkflowModel::getNodeStatus("queued"), WorkflowModel::NodeStatus::queued)
    EXPECT_EQ(WorkflowModel::getNodeStatus("que"), WorkflowModel::NodeStatus::queued)
    EXPECT_EQ(WorkflowModel::getNodeStatus("submitted"), WorkflowModel::NodeStatus::submitted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("sub"), WorkflowModel::NodeStatus::submitted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("active"), WorkflowModel::NodeStatus::active)
    EXPECT_EQ(WorkflowModel::getNodeStatus("act"), WorkflowModel::NodeStatus::active)
    EXPECT_EQ(WorkflowModel::getNodeStatus("aborted"), WorkflowModel::NodeStatus::aborted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("abo"), WorkflowModel::NodeStatus::aborted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("SHUTDOWN"), WorkflowModel::NodeStatus::shutdown)
    EXPECT_EQ(WorkflowModel::getNodeStatus("HALTED"), WorkflowModel::NodeStatus::halted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("hal"), WorkflowModel::NodeStatus::halted)
    EXPECT_EQ(WorkflowModel::getNodeStatus("RUNNING"), WorkflowModel::NodeStatus::running)
}

TEST_F(NodeStatusTest, MethodNodeStatusToString){
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::unknown), "unknown");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::suspended), "suspended");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::complete), "complete");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::queued), "queued");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::submitted), "submitted");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::active), "active");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::aborted), "aborted");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::shutdown), "shutdown");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::halted), "halted");
    EXPECT_EQ(WorkflowModel::nodeStatusToString(WorkflowModel::NodeStatus::running), "running");
}
}