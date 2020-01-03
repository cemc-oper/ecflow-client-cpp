project(ecflow_grpc)

add_library(ecflow_grpc STATIC)

find_package(gRPC CONFIG REQUIRED)

target_sources(ecflow_grpc PRIVATE
    src/ecflow_client.pb.cc
    src/ecflow_client.grpc.pb.cc)

target_include_directories(ecflow_grpc
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ecflow_client>
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_link_libraries(ecflow_grpc
    PUBLIC
    gRPC::grpc++)

add_library(EcflowClient::ecflow_grpc ALIAS ecflow_grpc)

install(DIRECTORY include/ecflow_client
    DESTINATION include)