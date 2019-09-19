#pragma once

namespace WorkflowModel {
enum class NodeType {
    Unknown = 0,
    Root,
    Suite,
    Family,
    Task,
    Alias,
    NonTaskNode,
    Meter
};
}