project(node_client)

add_executable(node_client)

target_sources(node_client PRIVATE
    main.cpp)

target_include_directories(node_client
    PUBLIC
        ${ecflow_client_cpp_SOURCE_DIR}/vendor)

target_link_libraries(node_client
    PRIVATE
        EcflowClient::ecflow_grpc)