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

using namespace ::WorkflowModel;

TEST_F(NodeStatusTest, MethodGetNodeStatus){
    struct TestCase{
        std::string s;
        NodeStatus status;
    };

    std::vector<TestCase> tests{
        {"unknown", NodeStatus::unknown},
        {"unk", NodeStatus::unknown},
        {"suspended", NodeStatus::suspended},
        {"sus", NodeStatus::suspended},
        {"complete", NodeStatus::complete},
        {"com", NodeStatus::complete},
        {"queued", NodeStatus::queued},
        {"que", NodeStatus::queued},
        {"submitted", NodeStatus::submitted},
        {"sub", NodeStatus::submitted},
        {"active", NodeStatus::active},
        {"act", NodeStatus::active},
        {"aborted", NodeStatus::aborted},
        {"abo", NodeStatus::aborted},
        {"SHUTDOWN", NodeStatus::shutedown},
        {"HALTED", NodeStatus::halted},
        {"hal", NodeStatus::halted},
        {"RUNNING", NodeStatus::running},
    };

    for(auto test: tests){
        EXPECT_EQ(getNodeStatus(test.s), test.status);
    }
}

TEST_F(NodeStatusTest, MethodNodeStatusToString){
    struct TestCase{
        NodeStatus status;
        std::string result;
    };

    std::vector<TestCase> tests{
        { NodeStatus::unknown, "unknown" },
        { NodeStatus::suspended, "suspended" },
        { NodeStatus::complete, "complete" },
        { NodeStatus::queued, "queued" },
        { NodeStatus::submitted, "submitted" },
        { NodeStatus::active, "active" },
        { NodeStatus::aborted, "aborted" },
        { NodeStatus::shutdown, "shutdown" },
        { NodeStatus::halted, "halted" },
        { NodeStatus::running, "running" },
    };

    for(auto test: tests){
        EXPECT_EQ(nodeStatusToString(test.status), result);
    }
}
}