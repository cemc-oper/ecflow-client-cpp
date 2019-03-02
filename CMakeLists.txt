cmake_minimum_required(VERSION 3.12)
project(ecflow_client_cpp)

set(CMAKE_CXX_STANDARD 14)

if(ENABLE_TESTS)
    find_package(GTest REQUIRED)
endif()

add_subdirectory(example)
add_subdirectory(src)