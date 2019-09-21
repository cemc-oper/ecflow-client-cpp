project(ecflow_util_standalone)

if (NOT ECFLOW_BUILD_DIR OR NOT ECFLOW_SOURCE_DIR)
    message(FATAL_ERROR "Please set ECFLOW_BUILD_DIR and ECFLOW_SOURCE_DIR")
endif ()

add_library(ecflow_util_standalone STATIC)

target_sources(ecflow_util_standalone PRIVATE
    src/ecflow_client_standalone.cpp)

target_include_directories(ecflow_util_standalone
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_link_libraries(ecflow_util_standalone
    PRIVATE
    Ecflow::Ecflow
    Boost::system
    Boost::filesystem
    Boost::date_time
    Boost::program_options
    Boost::serialization
    Boost::thread
    Boost::regex
    )

add_library(EclfowClientCPP::ecflow_util_standalone ALIAS ecflow_util_standalone)

install(DIRECTORY include/ecflow_client
    DESTINATION include)