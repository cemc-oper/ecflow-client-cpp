project(node_client)

add_executable(node_client)

target_sources(node_client PRIVATE
    main.cpp)

target_link_libraries(node_client
    PRIVATE
    EcflowClient::ecflow_grpc
    spdlog::spdlog_header_only
    )