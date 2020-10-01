
add_library(test SHARED edge_test.cc graph_test.cc node_test.cc)

target_link_libraries(test
    graphD
    ${GTEST_LIBRARIES})
