#ifndef __EDGE_TEST_H__
#define __EDGE_TEST_H__

#include <gtest/gtest.h>

class EdgeTest : public ::testing::Test
{
protected:
    void SetUp() override;
    
    std::string self_edge();
    std::string self_next();
    std::string self_move();

    std::string travel_node_level_1();
    std::string travel_node_level_2();
    std::string travel_node_level_n();

    void TearDown() override;
};

#endif
