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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${ecflow_client_cpp_SOURCE_DIR}/vendor>
    )

target_link_libraries(workflow_model
    PUBLIC
        Boost::boost
        EcflowClient::vendor
    )

add_library(EclfowClientCPP::workflow_model ALIAS workflow_model)

install(FILES
    src/bunch.h
    src/node.h
    src/node_status.h
    src/node_type.h
    src/node_variable.h
    src/workflow_node.h
    DESTINATION include)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()