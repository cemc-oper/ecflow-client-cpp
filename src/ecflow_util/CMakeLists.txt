project(ecflow_util)

if(NOT ECFLOW_BUILD_DIR OR NOT ECFLOW_SOURCE_DIR)
    message(FATAL_ERROR "Please set ECFLOW_BUILD_DIR and ECFLOW_SOURCE_DIR")
endif()

add_library(ecflow_util STATIC)

target_sources(ecflow_util PRIVATE
    src/ecflow_client.cpp)

target_include_directories(ecflow_util
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_link_libraries(ecflow_util
    PUBLIC
        workflow_model
    PRIVATE
        Ecflow::Ecflow
    INTERFACE
        Boost::system
        Boost::filesystem
        Boost::date_time
        Boost::program_options
        Boost::serialization
        Boost::thread
        Boost::regex
    )

add_library(EclfowClientCPP::ecflow_util ALIAS ecflow_util)

install(DIRECTORY include/ecflow_client
    DESTINATION include)