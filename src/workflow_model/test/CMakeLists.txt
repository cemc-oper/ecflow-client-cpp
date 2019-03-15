add_executable(test_workflow_model)

target_sources(test_workflow_model PRIVATE
	test_node.cpp
	test_main.cpp
	test_bunch.cpp
	test_node_variable.cpp
	test_workflow_node.cpp)

target_include_directories(test_workflow_model PRIVATE
    ${PROJECT_BINARY_DIR}/test
    )

target_link_libraries(test_workflow_model PRIVATE
    workflow_model
	GTest::GTest
	GTest::Main)

add_test(WorkflowModelTest test_workflow_model)