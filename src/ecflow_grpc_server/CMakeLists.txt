project(ecflow_grpc_server)

add_executable(ecflow_grpc_server)

target_sources(ecflow_grpc_server PRIVATE
    ecflow_client_service_impl.cpp
    main.cpp)

target_include_directories(ecflow_grpc_server
    PRIVATE
        ${ecflow_client_cpp_SOURCE_DIR}/vendor
    )

target_link_libraries(ecflow_grpc_server
    PRIVATE
        ecflow_grpc
        ecflow_util
        Boost::boost
    )