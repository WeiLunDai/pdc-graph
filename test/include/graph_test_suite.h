#ifndef __GRAPH_TEST_SUITE_H__
#define __GRAPH_TEST_SUITE_H__

#include "node_test.h"

TEST_F(NodeTest, self)
{
    EXPECT_EQ(self_name(), "I'm a Node");
    EXPECT_EQ(self_size(), "012345678910");
    EXPECT_EQ(self_isTo(), "01");
    EXPECT_EQ(self_next(), "0123456789");
    EXPECT_EQ(self_to_zero(), "main");
}

TEST_F(NodeTest, edit)
{
    EXPECT_EQ(add_one_node(), "new node");
    EXPECT_EQ(add_more_node(), "0123456789");
    EXPECT_EQ(del_one_node(), "012346789");
    EXPECT_EQ(del_more_node(), "0129");
}

#endif
