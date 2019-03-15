#include <gtest/gtest.h>
#include "../include/ecflow_client/workflow_model/node.h"

namespace {
class NodeTest: public ::testing::Test {
protected:
    NodeTest() = default;
    ~NodeTest() = default;

    void SetUp() override{}
    void TearDown() override{}
};

using namespace ::WorkflowModel;

TEST_F(NodeTest, MethodEmptyConstructor){
    WorkflowModel::Node node;
    EXPECT_EQ(node.name(), "");
    EXPECT_EQ(node.parent(), nullptr);
    EXPECT_EQ(node.status(), WorkflowModel::NodeStatus::unknown);
}

TEST_F(NodeTest, MethodConstructor){
    std::string node_name = "f1";
    auto node_status = NodeStatus::active;
    Node node{
        node_name,
        node_status
    };
    EXPECT_EQ(node.name(), node_name);
    EXPECT_EQ(node.status(), node_status);


    Node node2{
        node_name
    };
    EXPECT_EQ(node2.name(), node_name);
    EXPECT_EQ(node2.status(), NodeStatus::unknown);
}

TEST_F(NodeTest, MethodSetParent){
    auto f1 = std::make_shared<Node>("f1");
    auto t1 = std::make_shared<Node>("t1");
    auto t2 = std::make_shared<Node>("t2");
    f1->addChild(t1);
    f1->addChild(t2);
    EXPECT_EQ(t1->parent()->name(), f1->name());
    EXPECT_EQ(t1->parent()->name(), f1->name());
}

TEST_F(NodeTest, MethodAddChild){
    auto f1 = std::make_shared<Node>("f1");
    auto t1 = std::make_shared<Node>("t1");
    auto t2 = std::make_shared<Node>("t2");
    f1->addChild(t1);
    f1->addChild(t2);
    auto children = f1->children();
    EXPECT_EQ(children[0]->name(), t1->name());
    EXPECT_EQ(children[1]->name(), t2->name());
}

TEST_F(NodeTest, MethodNodePath){
    auto t1 = std::make_shared<Node>("t1");
    auto f2 = std::make_shared<Node>("f2");
    f2->addChild(t1);
    auto f1 = std::make_shared<Node>("f1");
    f1->addChild(f2);
    auto s1 = std::make_shared<Node>("s1");
    s1->addChild(f1);
    auto root = std::make_shared<Node>("");
    root->addChild(s1);
    EXPECT_EQ(t1->nodePath(), "/s1/f1/f2/t1");
    EXPECT_EQ(f2->nodePath(), "/s1/f1/f2");
    EXPECT_EQ(f1->nodePath(), "/s1/f1");
    EXPECT_EQ(s1->nodePath(), "/s1");
    EXPECT_EQ(root->nodePath(), "/");
}

TEST_F(NodeTest, MethodToJson){
    auto f1 = std::make_shared<Node>("f1");
    auto t1 = std::make_shared<Node>("t1");
    auto t2 = std::make_shared<Node>("t2");
    f1->addChild(t1);
    f1->addChild(t2);

    auto root_json = f1->toJson();
    auto expected_json = nlohmann::json{
        {"name", "f1"},
        {"status", 0},
        {"children",
            {
                {
                    {"name", "t1"}, {"status", 0}, {"children", {}}
                },
                {
                    {"name", "t2"}, {"status", 0}, {"children", {}}
                },
            }
        }
    };
    EXPECT_EQ(root_json["name"], expected_json["name"]);
    EXPECT_EQ(root_json["status"], expected_json["status"]);
    EXPECT_EQ(root_json["children"][0]["name"], expected_json["children"][0]["name"]);
}

}