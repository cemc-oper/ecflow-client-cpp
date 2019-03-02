project(workflow_model)

set(SOURCE_FILES
    src/node_status.cpp
    src/node.cpp
    )

add_library(workflow_model STATIC ${SOURCE_FILES})

target_include_directories(workflow_model
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${ecflow_client_cpp_SOURCE_DIR}/vendor
    INTERFACE
    ${PROJECT_SOURCE_DIR}/src
    ${ecflow_client_cpp_SOURCE_DIR}/vendor
    )


if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()