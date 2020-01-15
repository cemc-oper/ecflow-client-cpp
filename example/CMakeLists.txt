add_subdirectory(suite_status)

if(ENABLE_SERVER)
    add_subdirectory(status_records_client)
    add_subdirectory(node_client)
endif()