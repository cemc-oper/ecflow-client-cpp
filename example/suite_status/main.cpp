#include <iostream>
#include <ecflow_client.h>

int main() {
    EcflowUtil::EcflowClient client{"10.40.143.18", "31071"};
    client.sync();
    auto bunch = client.bunch();

    for(auto &node: bunch->children()){
        std::cout<<node->nodePath()<<" status: "
        <<WorkflowModel::nodeStatusToString(node->status())<<std::endl;
    }

    return 0;
}