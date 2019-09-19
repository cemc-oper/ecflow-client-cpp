project(workflow_model)

add_library(workflow_model STATIC)

target_sources(workflow_model PRIVATE
    src/node_status.cpp
    src/node.cpp
    src/bunch.cpp
    src/node_variable.cpp
    src/workflow_node.cpp)

target_include_directories(workflow_model
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_link_libraries(workflow_model
    PUBLIC
    Boost::boost
    EcflowClient::vendor
    )

add_library(EclfowClientCPP::workflow_model ALIAS workflow_model)

install(DIRECTORY include/ecflow_client
    DESTINATION include)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()