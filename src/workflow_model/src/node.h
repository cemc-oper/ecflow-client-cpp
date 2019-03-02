#pragma once

#include <string>

namespace WorkflowModel {

class Node {
public:
    void setName(const std::string &name);
    std::string name() const {
        return name_;
    }
private:
    std::string name_;

};

} // namespace WorkflowModel
