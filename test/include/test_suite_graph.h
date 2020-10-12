#ifndef __GRAPH_TEST_SUITE_H__
#define __GRAPH_TEST_SUITE_H__

#include "test_node.h"
#include "test_edge.h"
#include "test_graph.h"

// TEST_F(NodeTest, edit)
// {
//     EXPECT_EQ(add_one_node(), "new node");
//     EXPECT_EQ(add_more_node(), "0123456789");
//     EXPECT_EQ(del_one_node(), "012346789");
//     EXPECT_EQ(del_more_node(), "0129");
// }

// TEST_F(EdgeTest, self)
// {
//     EXPECT_EQ(self_edge(), "main->destination\n");
//     EXPECT_EQ(self_next(), "main->10\nmain->9\nmain->8\nmain->7\nmain->6\nmain->5\nmain->4\nmain->3\nmain->2\nmain->1\n");
//     EXPECT_EQ(self_move(), "main->0\n0->1\n1->2\n2->3\n3->4\n4->5\n5->6\n6->7\n7->8\n8->9\n");
//
// }
//
// TEST_F(EdgeTest, travel)
// {
//     EXPECT_EQ(travel_node_level_1(), "main->0\nmain->1\nmain->2\nmain->3\nmain->4\nmain->5\nmain->6\nmain->7\nmain->8\nmain->9\n");
// }

// TEST_F(GraphTest, func)
// {
//     EXPECT_EQ(find_node(), "main\n");
//     EXPECT_EQ(find_edge(), "main->N2\nN2\n");
//     EXPECT_EQ(nodeSize(), "012345678910");
//     EXPECT_EQ(edgeSize(), "012345678910");
//     EXPECT_EQ(add_node(), "main\n500\n501\n502\n503\n504\n");
//     EXPECT_EQ(add_edge(), "main->500\nmain->501\nmain->502\nmain->503\nmain->504\n500\n501\n502\n503\n504\n");
//     EXPECT_EQ(del_node(), "main\n500\n501\n502\n504\n");
//     EXPECT_EQ(del_edge(), "main->100\nmain->101\nmain->103\nmain->104\n100\n101\n102\n103\n104\n");
//     EXPECT_EQ(runDFS(), "3->4\n4->6\n6->5\n5->1\n1->2\n2\n");
//     EXPECT_EQ(runBFS(), "3->4\n3->5\n4->6\n5->1\n6\n1->2\n2\n");
//     EXPECT_TRUE(exportGraph());
// }

#endif
