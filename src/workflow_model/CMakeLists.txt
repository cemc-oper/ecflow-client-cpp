project(workflow_model)

find_package(Boost REQUIRED)

set(SOURCE_FILES
    src/node_status.cpp
    src/node.cpp
    src/bunch.cpp
    src/node_variable.cpp
	src/workflow_node.cpp
    )

add_library(workflow_model STATIC
    ${SOURCE_FILES})

target_include_directories(workflow_model
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${ecflow_client_cpp_SOURCE_DIR}/vendor
    )

target_link_libraries(workflow_model
    PUBLIC
        Boost::boost)


add_library(EclfowClient::workflow_model ALIAS workflow_model)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()