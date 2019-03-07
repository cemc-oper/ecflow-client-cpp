cmake_minimum_required(VERSION 3.12)
project(ecflow_client_cpp)

set(CMAKE_CXX_STANDARD 14)

option(ENABLE_TESTS "Enable tests" OFF)

if(ENABLE_TESTS)
    message("ENABLE TESTS...")
    find_package(GTest REQUIRED)
    enable_testing()
endif()

add_subdirectory(example)
add_subdirectory(src)