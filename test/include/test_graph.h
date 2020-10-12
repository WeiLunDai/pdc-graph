#pragma once

#include "graph.h"
#include <gtest/gtest.h>

/* TestGraph - func
 *  . add node
 *  . find node
 *  . delete node
 *  . find edge
 *  . node size
 *  . edge size
 *
 * */
TEST(TestGraph, func)
{
    Graph g = Graph();
    g.add("main");
    EXPECT_EQ(g.find("main")->info(), "main");

    g.add("main", "N2");
    EXPECT_EQ(g.find("main", "N2")->info(), "main->N2\n");

    for (int i = 0; i < 10; i++)
    {
        g.add("main", std::to_string(i));
    }

    EXPECT_EQ(g.nodeSize(), 12);
    EXPECT_EQ(g.edgeSize(), 11);

    g.del("N2");

    EXPECT_EQ(g.nodeSize(), 11);
    EXPECT_EQ(g.edgeSize(), 10);
}

/* TestGraph - adv
 *  . BFS
 *  . DFS
 *
 * */
TEST(TestGraph, adv)
{
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "3"} };

    Graph g(gt);
    EXPECT_EQ(g.breathFirstSearch("1")->info(),
            "1->2\n1->3\n2\n3\n");
    EXPECT_EQ(g.depthFirstSearch("1")->info(),
            "1->2\n2->3\n3\n");
}
