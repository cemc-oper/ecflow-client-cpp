project(ecflow_grpc)

add_library(ecflow_grpc STATIC)

target_sources(ecflow_grpc PRIVATE
    ecflow_client.pb.cc
    ecflow_client.grpc.pb.cc)

target_include_directories(ecflow_grpc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(ecflow_grpc
    PUBLIC
        gRPC::grpc++)

add_library(EcflowClient::ecflow_grpc ALIAS ecflow_grpc)