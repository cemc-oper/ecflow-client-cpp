project(ecflow_grpc_server)

add_executable(ecflow_grpc_server)

find_package(gRPC CONFIG REQUIRED)

target_sources(ecflow_grpc_server PRIVATE
    src/ecflow_client_service_impl.cpp
    src/main.cpp)

target_link_libraries(ecflow_grpc_server
    PRIVATE
    ecflow_grpc
    ecflow_util
    Boost::boost
    spdlog::spdlog_header_only
    CLI11::CLI11
    )