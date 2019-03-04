project(example_suite_status)

add_executable(example_suite_status
    main.cpp
    )

target_link_libraries(example_suite_status
    PUBLIC
        ecflow_util
    )
