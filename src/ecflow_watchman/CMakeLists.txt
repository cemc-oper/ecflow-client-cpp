project(ecflow_watchman)

find_path(HIREDIS_HEADER hiredis)
find_library(HIREDIS_LIB NAMES libhiredis.a)

find_path(REDIS_PLUS_PLUS_HEADER sw)
find_library(REDIS_PLUS_PLUS_LIB NAMES libredis++.a)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)

message(STATUS "HIREDIS_HEADER ${HIREDIS_HEADER}")
message(STATUS "HIREDIS_LIB ${HIREDIS_LIB}")
message(STATUS "REDIS_PLUS_PLUS_HEADER ${REDIS_PLUS_PLUS_HEADER}")
message(STATUS "REDIS_PLUS_PLUS_LIB ${REDIS_PLUS_PLUS_LIB}")

add_executable(ecflow_watchman)

target_include_directories(ecflow_watchman
    PRIVATE
    ${HIREDIS_HEADER}
    ${REDIS_PLUS_PLUS_HEADER})

target_sources(ecflow_watchman PRIVATE
    src/main.cpp
    src/watch.cpp
    src/watch_all.cpp
    src/storer.cpp
    src/collector.cpp)

target_link_libraries(ecflow_watchman
    PRIVATE
    ecflow_util
    Boost::boost
    ${HIREDIS_LIB}
    ${REDIS_PLUS_PLUS_LIB}
    yaml-cpp
    spdlog::spdlog_header_only
    fmt::fmt-header-only
    date::date
    CLI11::CLI11
    )