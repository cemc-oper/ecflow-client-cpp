#include <iostream>
#include "../../src/ecflow_util/include/ecflow_client/ecflow_client.h"

int main(int argc, char* argv[]) {
    EcflowUtil::EcflowClient client{"10.40.143.18", "31071"};
    client.sync();
    auto bunch = client.bunch();

    for(auto &node: bunch->children()){
        std::cout<<node->nodePath()<<" status: "
            <<WorkflowModel::nodeStatusToString(node->status())
            <<std::endl;
    }

    auto node = client.getWorkflowNode("/meso_post/00/initial");
    std::cout<<node->toJson().dump(2)<<std::endl;

    return 0;
}