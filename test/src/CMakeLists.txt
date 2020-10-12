
add_library(test_graphD SHARED test_node.cc test_edge.cc test_graph.cc)

target_link_libraries(test_graphD
    graphD
    ${GTEST_LIBRARIES})
