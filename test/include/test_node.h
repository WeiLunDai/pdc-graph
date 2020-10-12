#pragma once

#include <gtest/gtest.h>
#include <string>
#include "graph.h"

// class NodeTest : public ::testing::Test
// {
// protected:
//     void SetUp() override;
//
//     std::string self_name();
//     std::string self_size();
//     std::string self_isTo();
//     std::string self_next();
//     std::string self_to_zero();
//
//     std::string add_one_node();
//     std::string add_more_node();
//     std::string del_one_node();
//     std::string del_more_node();
//
//     void TearDown() override;
// };


/* TestNode - self
 *  . info of one node
 *  . info of to node when edge size is zero
 *  . edgeSize
 *  . isTo when exist
 *  . isTo when not exist
 *
 * */
TEST(TestNode, self)
{
    Node n = Node("Main");
    EXPECT_EQ(n.info(), "Main");

    EXPECT_EQ(n.to()->info(), "Main");

    Node na[10];
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_EQ(n.edgeSize(), i);

        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
    }
    EXPECT_EQ(n.edgeSize(), 10);

    Node target = Node("1");
    EXPECT_TRUE(n.isTo( &target ));

    target = Node("11");
    EXPECT_FALSE(n.isTo( &target ));
}

TEST(TestNode, edit)
{
    Node n = Node("Main");
    Node na[10];
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
        n.next();
        EXPECT_EQ(n.to()->info(), std::to_string(i));
    }

    Node target = Node("4");
    n.del( &target );
    EXPECT_FALSE( target.isTo(&target) );
}

// TEST_F(NodeTest, self)
// {
//     EXPECT_EQ(self_name(), "I'm a Node");
//     EXPECT_EQ(self_size(), "012345678910");
//     EXPECT_EQ(self_isTo(), "01");
//     EXPECT_EQ(self_next(), "0123456789");
//     EXPECT_EQ(self_to_zero(), "main");
// }
//
// TEST_F(NodeTest, edit)
// {
//     EXPECT_EQ(add_one_node(), "new node");
//     EXPECT_EQ(add_more_node(), "0123456789");
//     EXPECT_EQ(del_one_node(), "012346789");
//     EXPECT_EQ(del_more_node(), "0129");
// }

// class GraphTest : public ::testing::Test
// {
// private:
//     Graph::GraphTable gt {
//         {"1", "2"}, {"1", "3"}, {"2", "4"},
//         {"2", "6"}, {"3", "4"}, {"3", "5"},
//         {"4", "6"}, {"5", "1"}, {"6", "5"} } ;
//     Graph g_add;
//     Graph g_find;
// protected:
//     void SetUp() override
//     {
//         g_find = Graph(gt);
//     }

    // bool add_node_empty()
    // {
    //     return nullptr != g_add.add();
    // }
    //
    // bool add_node_exist()
    // {
    //     std::string t = ("7");
    //     g_add.add_node(t.c_str());
    //     return nullptr == g_add.add_node(t.c_str());
    // }
    //
    // bool add_edge_empty()
    // {
    //     return nullptr != g_add.add_edge("2", "3");
    // }
    //
    // bool add_edge_exist()
    // {
    //     g_add.add_edge("5", "6");
    //     return nullptr == g_add.add_edge("5", "6");
    // }
    //
    // bool find_node_not_exist()
    // {
    //     return nullptr == g_find.find_node("1");
    // }
    //
    // bool find_node_exist()
    // {
    //     g_find.add_node("1");
    //     return nullptr != g_find.find_node("1");
    // }
    //
    // bool find_edge_not_exist()
    // {
    //     return nullptr == g_find.find_edge("98", "99");
    // }
    //
    // bool find_edge_exist()
    // {
    //     g_find.add_edge("100", "101");
    //     return nullptr != g_find.add_edge("100", "101");
    // }
// };

// TEST_F(GraphTest, add)
// {
    //EXPECT_TRUE(add_node_empty());
    //EXPECT_TRUE(add_node_exist());
    //EXPECT_TRUE(add_edge_empty());
    //EXPECT_TRUE(add_edge_exist());
// }
//
// TEST_F(GraphTest, find)
// {
    // EXPECT_TRUE(find_node_exist());
    // EXPECT_TRUE(find_node_not_exist());
    // EXPECT_TRUE(find_edge_exist());
    // EXPECT_TRUE(find_edge_not_exist());
// }
//
