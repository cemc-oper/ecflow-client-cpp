project(ecflow_watchman)

add_executable(ecflow_watchman)

target_sources(ecflow_watchman PRIVATE
    src/main.cpp
    src/watch.cpp)

target_link_libraries(ecflow_watchman
    PRIVATE
    ecflow_util
    EcflowClient::vendor
    Boost::boost
    )