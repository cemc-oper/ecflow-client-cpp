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
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${ecflow_client_cpp_SOURCE_DIR}/vendor>
    )

target_link_libraries(workflow_model
    PUBLIC
        Boost::boost)

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