#pragma once
#include <string>

namespace ecflow_watchman {

class EcflowCollector {
public:
    EcflowCollector(
            std::string owner,
            std::string repo,
            std::string ecflow_host,
            std::string ecflow_port);

    std::string getStatusJsonString();

private:
    std::string owner_;
    std::string repo_;
    std::string ecflow_host_;
    std::string ecflow_port_;
};


}
