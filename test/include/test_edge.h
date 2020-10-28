#pragma once

#include "graph.h"
#include <gtest/gtest.h>

/* TestEdge - self
 *  . edge iteration on node
 *  . edge move on node
 *
 * */
TEST(TestEdge, self)
{
    Node n = Node("main");
    Node na[10];
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
    }
    Edge e(&n);

    e.begin();
    for (size_t i = 0; i < e.here()->edgeSize(); i++)
    {
        EXPECT_EQ(e.info(), "main->" + std::to_string(i) + "\n");
        e.next();
    }
    e.begin();
    e.move();

    EXPECT_EQ(e.to()->info(), e.here()->info());

}
