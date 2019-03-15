project(status_records_client)

add_executable(status_records_client)

target_sources(status_records_client PRIVATE
    main.cpp)

target_include_directories(status_records_client
    PUBLIC
        ${ecflow_client_cpp_SOURCE_DIR}/vendor)

target_link_libraries(status_records_client
    PRIVATE
        EcflowClient::ecflow_grpc)