cmake_minimum_required(VERSION 3.12)
project(ecflow_client_cpp)

set(CMAKE_CXX_STANDARD 14)

set(EcflowClientCPP_VERSION 0.0.1)

find_package(spdlog CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_SERVER "Enable GRPC server" OFF)

if(ENABLE_TESTS)
    message("ENABLE TESTS...")
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
endif()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(example)

install(TARGETS workflow_model ecflow_util ecflow_watchman Ecflow
    EXPORT EcflowClientCppTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )
if(ENABLE_SERVER)
    install(TARGETS ecflow_grpc_server Ecflow
        EXPORT EcflowClientCppTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    EcflowClientCppConfigVersion.cmake
    VERSION ${EcflowClientCPP_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT EcflowClientCppTargets
    FILE EcflowClientCppTargets.cmake
    NAMESPACE EcflowClientCPP::
    DESTINATION lib/cmake/EcflowClientCPP)


