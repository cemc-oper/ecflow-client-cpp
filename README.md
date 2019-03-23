# ecflow-client-cpp

A client for ecflow using ecflow's c++ API 
including a tree-like model for workflow, 
an ecflow client to get status or node information,
and a gRPC server to collect data from ecflow server.

## Requirements

### ecFlow

Build ecFlow server and client 
(python and GUI components are not required).  

### Boost

`ecFlow` uses some boost complied libraries:

- system
- filesystem
- date_time
- program_options
- serialization
- thread
- regex

And `ecflow-client-cpp` uses some boost header-only libraries.

### gRPC

ecflow client server is based on gRPC.

### gtest

To build tests, gtest is required.

## Installation

Use CMake to build the project from source code.

Some variables should be set to help find external libraries.

- `ECFLOW_SOURCE_DIR`: ecFlow's source code directory. 
- `ECFLOW_BUILD_DIR`: ecFlow's build directory.

## Getting Started

Use binary program `ecflow_grpc_server` to run a gRPC server.

```bash
./ecflow_grpc_server --rpc-target="[::]:31181"
```

gRPC client will get ecFlow status and node information from this server.

See `example` directory for more examples.

## License

Copyright &copy; 2019, Perilla Roc.

`ecflow-client-cpp` is licensed under [GPL v3.0](LICENSE.md)

