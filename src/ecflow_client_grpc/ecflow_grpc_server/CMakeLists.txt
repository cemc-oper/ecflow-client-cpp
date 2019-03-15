project(ecflow_grpc_server)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

find_package(Boost REQUIRED)

set(SRC_FILES
    ${ecflow_client_grpc_SOURCE_DIR}/ecflow_client.grpc.pb.cc
    ${ecflow_client_grpc_SOURCE_DIR}/ecflow_client.pb.cc
    ecflow_client_service_impl.cpp
    main.cpp
    )

add_executable(ecflow_grpc_server
    ${SRC_FILES}
    )

target_include_directories(ecflow_grpc_server
    PRIVATE
        ${ecflow_client_grpc_SOURCE_DIR}
        ${ecflow_client_cpp_SOURCE_DIR}/vendor
    )

target_link_libraries(ecflow_grpc_server
    PUBLIC
        ecflow_util
        gRPC::grpc++
        Boost::boost
    )