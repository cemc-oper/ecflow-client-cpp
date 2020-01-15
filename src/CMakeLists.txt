add_subdirectory(workflow_model)
add_subdirectory(ecflow_util)
add_subdirectory(ecflow_util_standalone)
add_subdirectory(ecflow_watchman)

if(ENABLE_SERVER)
    add_subdirectory(ecflow_grpc)
    add_subdirectory(ecflow_grpc_server)
endif()