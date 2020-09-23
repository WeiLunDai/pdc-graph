#include "graph.h"
#include "gtest/gtest.h"

class GraphTest : public ::testing::Test
{
private:
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "4"},
        {"2", "6"}, {"3", "4"}, {"3", "5"},
        {"4", "6"}, {"5", "1"}, {"6", "5"} } ;
    Graph g_add;
    Graph g_find;
protected:
    void SetUp() override 
    {
        g_find = Graph(gt);
    }

    bool add_node_empty()
    {
        return nullptr != g_add.add_node("1");
    }

    bool add_node_exist()
    {
        std::string t = ("7");
        g_add.add_node(t.c_str());
        return nullptr == g_add.add_node(t.c_str());
    }

    bool add_edge_empty()
    {
        return nullptr != g_add.add_edge("2", "3");
    }

    bool add_edge_exist()
    {
        g_add.add_edge("5", "6");
        return nullptr == g_add.add_edge("5", "6");
    }

    bool find_node_not_exist()
    {
        return nullptr == g_find.find_node("1");
    }

    bool find_node_exist()
    {
        g_find.add_node("1");
        return nullptr != g_find.find_node("1");
    }

    bool find_edge_not_exist()
    {
        return nullptr == g_find.find_edge("98", "99");
    }

    bool find_edge_exist()
    {
        g_find.add_edge("100", "101");
        return nullptr != g_find.add_edge("100", "101");
    }
};

TEST_F(GraphTest, add)
{
    //EXPECT_TRUE(add_node_empty());
    //EXPECT_TRUE(add_node_exist());
    //EXPECT_TRUE(add_edge_empty());
    //EXPECT_TRUE(add_edge_exist());
}

TEST_F(GraphTest, find)
{
    // EXPECT_TRUE(find_node_exist());
    // EXPECT_TRUE(find_node_not_exist());
    // EXPECT_TRUE(find_edge_exist());
    // EXPECT_TRUE(find_edge_not_exist());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
