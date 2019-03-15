project(node_client)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(node_client)

target_sources(node_client PRIVATE

    ${ecflow_client_grpc_SOURCE_DIR}/ecflow_client.grpc.pb.cc
    ${ecflow_client_grpc_SOURCE_DIR}/ecflow_client.pb.cc
    main.cpp)

target_include_directories(node_client
    PUBLIC
        ${ecflow_client_grpc_SOURCE_DIR}
        ${ecflow_client_cpp_SOURCE_DIR}/vendor)

target_link_libraries(node_client
    PUBLIC
        gRPC::grpc++)