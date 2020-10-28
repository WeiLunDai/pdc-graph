#pragma once

#include <gtest/gtest.h>
#include <string>
#include "graph.h"

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

/* TestNode - edit
 *  . add node
 *  . consistency of data
 *  . delete node
 * */
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

