project(ecflow_util)

if(NOT ECFLOW_BUILD_DIR OR NOT ECFLOW_SOURCE_DIR)
    message(FATAL_ERROR "Please set ECFLOW_BUILD_DIR and ECFLOW_SOURCE_DIR")
endif()

find_package(Boost
    REQUIRED
    COMPONENTS
        system
        filesystem
        date_time
        program_options
        serialization
        thread
        regex
    )

add_library(ecflow_util STATIC)

target_sources(ecflow_util PRIVATE
    src/ecflow_client.cpp)

target_include_directories(ecflow_util
    PRIVATE
        ${ECFLOW_SOURCE_DIR}/ACore/src
        ${ECFLOW_SOURCE_DIR}/ANattr/src
        ${ECFLOW_SOURCE_DIR}/ANode/src
        ${ECFLOW_SOURCE_DIR}/Base/src
        ${ECFLOW_SOURCE_DIR}/Base/src/cts
        ${ECFLOW_SOURCE_DIR}/Base/src/stc
        ${ECFLOW_SOURCE_DIR}/CSim/src
        ${ECFLOW_SOURCE_DIR}/Client/src
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

target_link_libraries(ecflow_util
    PUBLIC
        workflow_model
    PRIVATE
        ${ECFLOW_BUILD_DIR}/Client/liblibclient.a
        ${ECFLOW_BUILD_DIR}/Base/libbase.a
        ${ECFLOW_BUILD_DIR}/CSim/liblibsimu.a
        ${ECFLOW_BUILD_DIR}/ANode/libnode.a
        ${ECFLOW_BUILD_DIR}/ANattr/libnodeattr.a
        ${ECFLOW_BUILD_DIR}/ACore/libcore.a
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