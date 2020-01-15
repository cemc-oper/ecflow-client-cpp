# ecflow-client-cpp

A client for ecflow using ecflow's c++ API including:

- A tree-like model for workflow
- An ecflow client to get status or node information
- A gRPC server to collect data from ecflow server
- A watcher to watch multiply ecflow servers

## Requirements

All requirements except ecFlow and Boost can be installed by [vcpkg](https://github.com/microsoft/vcpkg).

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

Boost 1.53.0 is suggested to build ecFlow.

### gRPC

ecflow client server is based on gRPC.

### gtest

To build tests, gtest is required.

### spdlog

Logs are printed by [spdlog](https://github.com/gabime/spdlog).

### CLI11

Commands use [CLI11](https://github.com/CLIUtils/CLI11) to parse command line options.

### nlohmann/json

We use [nlohmann/json](https://github.com/nlohmann/json) to generate JSON string.

### HowardHinnant/date

`ecflow_watchman` uses [HowardHinnant/date](https://github.com/HowardHinnant/date) to generate data string.

### yaml-cpp

`ecflow_watchman` uses YAML config file.

### redis-plus-plus

`ecflow_watchman` saves ecflow status into redis server.

## Installation

Use CMake to build the project from source code.

Some variables should be set to help find external libraries.

- `ECFLOW_SOURCE_DIR`: ecFlow's source code directory. 
- `ECFLOW_BUILD_DIR`: ecFlow's build directory.
- `BOOST_ROOT`: boost root directory.
- `Boost_NO_SYSTEM_PATHS=on`: disable system boost search because ecFlow uses a specific version of Boost.

Some variables control which components to build.

- `ENABLE_SERVER`: build grpc server and examples.
- `ENABLE_TESTS`: build all tests.

## Getting Started

There are several command line tools.

### ecflow_watchman

Run `ecflow_watchman all` to watch several ecFlow servers defined in a config file.

```bash
ecflow_watchman watch-all --config-file /path/to/config/file
```

The statuses of all ecFlow servers are stored into a Redis server.

For an ecflow server with `owner: nwp_xp` and `repo: nwpc_op`, the status will be stored using key `nwp_xp/nwpc_op/stats`.


### ecflow gRPC server

Use binary program `ecflow_grpc_server` to run a gRPC server.

```bash
./ecflow_grpc_server --rpc-target="[::]:31181"
```

gRPC client will get ecFlow status and node information from this server.

See `example` directory for more examples.

## License

Copyright &copy; 2019-2020, Perilla Roc.

`ecflow-client-cpp` is licensed under [GPL v3.0](LICENSE.md)

