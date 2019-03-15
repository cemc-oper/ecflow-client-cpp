project(example_suite_status)

add_executable(example_suite_status)

target_sources(example_suite_status PRIVATE
    main.cpp)

target_link_libraries(example_suite_status
    PUBLIC
        EclfowClientCPP::ecflow_util
    )
