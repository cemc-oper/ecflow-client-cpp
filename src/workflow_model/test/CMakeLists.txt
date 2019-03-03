set(TEST_MAIN_SRCS
    test_node.cpp
    test_main.cpp
    test_bunch.cpp)

add_executable(test_workflow_model_main ${TEST_MAIN_SRCS})

target_include_directories(test_workflow_model_main PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}/test
    )

target_link_libraries(test_workflow_model_main
    workflow_model
    ${GTEST_BOTH_LIBRARIES}
    pthread)

add_test(WorkflowModelTest test_workflow_model_main)