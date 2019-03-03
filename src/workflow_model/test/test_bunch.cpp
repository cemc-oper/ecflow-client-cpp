#include <gtest/gtest.h>
#include <bunch.h>

namespace {
class BunchTest: public ::testing::Test{
protected:
    BunchTest() = default;
    ~BunchTest() = default;

    void SetUp() override{}
    void TearDown() override{}
};

using namespace ::WorkflowModel;

TEST_F(BunchTest, MethodConstructor){
    auto bunch = std::make_shared<Bunch>("nwpc_op", NodeStatus::queued);

    EXPECT_EQ(bunch->name(), "nwpc_op");
    EXPECT_EQ(bunch->status(), NodeStatus::queued);

    auto empty_bunch = std::make_shared<Bunch>();
    EXPECT_EQ(empty_bunch->name(), "");
    EXPECT_EQ(empty_bunch->status(), NodeStatus::unknown);
}

TEST_F(BunchTest, MethodFindNode){
    auto bunch = std::make_shared<Bunch>("nwpc_op", NodeStatus::queued);
    auto suite = std::make_shared<Node>("suite1", NodeStatus::queued);
    bunch->addChild(suite);
    auto f1 = std::make_shared<Node>("f1", NodeStatus::complete);
    suite->addChild(f1);
    auto t1 = std::make_shared<Node>("t1", NodeStatus::complete);
    f1->addChild(t1);
    auto f2 = std::make_shared<Node>("f2", NodeStatus::queued);
    suite->addChild(f2);
    auto t2 = std::make_shared<Node>("t2", NodeStatus::queued);
    f2->addChild(t2);

    auto node1 = bunch->findNode("/suite1/f1/t1");
    EXPECT_EQ(node1, t1);
}

TEST_F(BunchTest, MethodAddNode){
    auto bunch = std::make_shared<Bunch>();
    auto t1 = bunch->addNode("/suite1/f1/t1");
    auto t2 = bunch->addNode("/suite1/f1/t2");
    auto t3 = bunch->addNode("/suite1/f2/t3");

    EXPECT_EQ(t1->nodePath(), "/suite1/f1/t1");
    EXPECT_EQ(t2->nodePath(), "/suite1/f1/t2");
    EXPECT_EQ(t3->nodePath(), "/suite1/f2/t3");

    auto f1 = bunch->findNode("/suite1/f1");
    EXPECT_TRUE(f1);
}

TEST_F(BunchTest, MethodAddNodeStatus){
    auto bunch = std::make_shared<Bunch>();
    auto t1 = bunch->addNodeStatus(NodeStatusRecord{"/suite1/f1/t1", "complete"});
    auto t2 = bunch->addNodeStatus(NodeStatusRecord{"/suite1/f1/t2", "active"});
    auto t3 = bunch->addNodeStatus(NodeStatusRecord{"/suite1/f2/t3", "queued"});

    EXPECT_EQ(t1->nodePath(), "/suite1/f1/t1");
    EXPECT_EQ(t1->status(), NodeStatus::complete);
    EXPECT_EQ(t2->nodePath(), "/suite1/f1/t2");
    EXPECT_EQ(t2->status(), NodeStatus::active);
    EXPECT_EQ(t3->nodePath(), "/suite1/f2/t3");
    EXPECT_EQ(t3->status(), NodeStatus::queued);

    auto f1 = bunch->findNode("/suite1/f1");
    EXPECT_TRUE(f1);
}

}