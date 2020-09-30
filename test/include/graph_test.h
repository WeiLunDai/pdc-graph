#ifndef __GRAPH_TEST_H__
#define __GRAPH_TEST_H__

#include <gtest/gtest.h>

class GraphTest : public ::testing::Test
{
protected:
    void SetUp() override;

    std::string find_node();
    std::string find_edge();
    std::string nodeSize();
    std::string edgeSize();

    std::string add_node();
    std::string add_edge();
    std::string del_node();
    std::string del_edge();

    std::string runDFS();
    std::string runBFS();

    bool exportGraph();

    void TearDown() override;
};

#endif
