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

TEST_F(EdgeTest, self)
{
    EXPECT_EQ(self_edge(), "main->destination\n");
    EXPECT_EQ(self_next(), "main->10\nmain->9\nmain->8\nmain->7\nmain->6\nmain->5\nmain->4\nmain->3\nmain->2\nmain->1\n");
    EXPECT_EQ(self_move(), "main->0\n0->1\n1->2\n2->3\n3->4\n4->5\n5->6\n6->7\n7->8\n8->9\n");

    EXPECT_EQ(travel_node_level_1(), "0123456789");
}

#endif
