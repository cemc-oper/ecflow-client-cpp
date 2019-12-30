#pragma once
#include <string>

namespace ecflow_watchman {

class EcflowCollector {
public:
    EcflowCollector(
            const std::string &owner,
            const std::string &repo,
            const std::string &ecflow_host,
            const std::string &ecflow_port);

    std::string getStatusJsonString();

private:
    std::string owner_;
    std::string repo_;
    std::string ecflow_host_;
    std::string ecflow_port_;
};


}
