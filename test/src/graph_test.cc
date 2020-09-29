#include "graph_test.h"
#include "graph.h"

void GraphTest::SetUp()
{
}

std::string GraphTest::find_node()
{
    Graph g = Graph();
    Node n = Node("main");
    g.add(n);

    return g.info();
}

std::string GraphTest::find_edge()
{
    Graph g = Graph();
    Node n = Node("main");
    Node n2 = Node("N2");
    n.add(n2);
    g.add(n);

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
        g.add(na[i]);
        tmp += std::to_string(g.nodeSize());
    }
    return tmp;
}

std::string GraphTest::edgeSize()
{
    std::string tmp;
    Graph g;
    tmp += std::to_string(g.edgeSize());
    Node n = Node("main");
    Node na[10];

    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(na[i]);
        n.next();

        Edge e = Edge(n);
        g.add(e);
        tmp += std::to_string(g.edgeSize());
    }
    return tmp;
}

std::string GraphTest::add_node()
{
    Node n = Node("main");
    Node na[5];
    Graph g;
    g.add(n);
    for (int i = 0; i < 5; i++)
    {
        na[i] = Node(std::to_string(i+500));
        g.add(na[i]);
    }

    return g.info();
}

std::string GraphTest::add_edge()
{
    Graph g;
    Node n = Node("main");
    Node na[5];

    for (int i = 0; i < 5; i++)
    {
        na[i] = Node(std::to_string(i+500));
        n.add(na[i]);
        n.next();

        Edge e = Edge(n);
        g.add(e);
    }

    return g.info();
}

std::string GraphTest::del_node()
{
    Node n = Node("main");
    Node na[5];
    Graph g;
    g.add(n);
    for (int i = 0; i < 5; i++)
    {
        na[i] = Node(std::to_string(i+500));
        g.add(na[i]);
    }

    Node tmp_n;
    tmp_n = Node(std::to_string(503));
    g.del(tmp_n);

    return g.info();
}

std::string GraphTest::del_edge()
{
    Graph g;
    Node n = Node("main");
    Node na[5];

    for (int i = 0; i < 5; i++)
    {
        na[i] = Node(std::to_string(i+100));
        n.add(na[i]);
        n.next();

        Edge e = Edge(n);
        g.add(e);
    }

    n.begin();
    Edge en = Edge(n);
    en.next();
    en.next();
    g.del(en);

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
    Graph tmp;
    tmp = g.depthFirstSearch(n);

    return tmp.info();
}

std::string GraphTest::runBFS()
{
    Node n = Node("3");
    Graph::GraphTable gt {
        {"1", "2"}, {"1", "3"}, {"2", "4"},
        {"2", "6"}, {"3", "4"}, {"3", "5"},
        {"4", "6"}, {"5", "1"}, {"6", "5"} } ;

    Graph g(gt);
    Graph tmp;
    tmp = g.breathFirstSearch(n);

    return tmp.info();
}

void GraphTest::TearDown()
{
}
