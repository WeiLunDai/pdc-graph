#include "graph_test.h"
#include "graph.h"
#include <string>

void GraphTest::SetUp()
{
}

std::string GraphTest::find_node()
{
    Graph g = Graph();
    Node n = Node("main");
    g.add(&n);

    return g.info();
}

std::string GraphTest::find_edge()
{
    std::string name[] = {"main", "N2"};
    Graph g;
    g.add(name[0], name[1]);

    return g.info();
}

std::string GraphTest::nodeSize()
{
    std::string tmp;
    Node na[10];
    Graph g;
    tmp += std::to_string(g.nodeSize());
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        g.add(&na[i]);
        tmp += std::to_string(g.nodeSize());
    }
    return tmp;
}

std::string GraphTest::edgeSize()
{
    std::string tmp;
    Graph g;
    tmp += std::to_string(g.edgeSize());

    for (int i = 0; i < 10; i++)
    {
        g.add(std::string("main"), std::to_string(i));
        tmp += std::to_string(g.edgeSize());
    }
    return tmp;
}

std::string GraphTest::add_node()
{
    Graph g;
    g.add(std::string("main"));

    for (int i = 0; i < 5; i++)
    {
        g.add(std::to_string(i+500));
    }

    return g.info();
}

std::string GraphTest::add_edge()
{
    Graph g;

    for (int i = 0; i < 5; i++)
    {
        g.add(std::string("main"), std::to_string(i+500));
    }

    return g.info();
}

std::string GraphTest::del_node()
{
    Node na[5];
    Graph g;
    g.add(std::string("main"));
    for (int i = 0; i < 5; i++)
    {
        g.add(std::to_string(i+500));
    }

    g.del(std::to_string(503));

    return g.info();
}

std::string GraphTest::del_edge()
{
    Graph g;

    for (int i = 0; i < 5; i++)
    {
        g.add(std::string("main"), std::to_string(i+100));
    }

    g.del(std::string("main"), std::string("102"));

    return g.info();
}

std::string GraphTest::runDFS()
{
    Node n = Node("3");
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "4"},
        {"2", "6"}, {"3", "4"}, {"3", "5"},
        {"4", "6"}, {"5", "1"}, {"6", "5"} } ;

    Graph g(gt);
    return g.depthFirstSearch(&n)->info();
}

std::string GraphTest::runBFS()
{
    Node n = Node("3");
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "4"},
        {"2", "6"}, {"3", "4"}, {"3", "5"},
        {"4", "6"}, {"5", "1"}, {"6", "5"} } ;

    Graph g(gt);
    return g.breathFirstSearch(&n)->info();
}

bool GraphTest::exportGraph()
{
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "4"},
        {"2", "6"}, {"3", "4"}, {"3", "5"},
        {"4", "6"}, {"5", "1"}, {"6", "5"} } ;

    //char title[] = "title";
    Graph g(gt);
    //g.exportPng(title);
    return true;
}

void GraphTest::TearDown()
{
}
