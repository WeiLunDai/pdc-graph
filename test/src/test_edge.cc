#include "test_edge.h"
#include "graph.h"
#include <queue>

void EdgeTest::SetUp()
{
}

std::string EdgeTest::self_edge()
{
    Node n = Node("main");
    Node n1 = Node("destination");
    n.add(&n1);
    Edge e(&n);
    return e.info();
}

std::string EdgeTest::self_next()
{
    Node n = Node("main");
    Node na[10];
    for (int i = 10; i > 0; i--)
    {
        na[10 - i] = Node(std::to_string(i));
        n.add(&na[10 - i]);
    }
    Edge e(&n);
    std::string tmp;
    e.begin();
    for (size_t i = 0; i < e.here()->edgeSize(); i++)
    {
        tmp += e.info();
        e.next();
    }
    return tmp;
}

std::string EdgeTest::self_move()
{
    Node n = Node("main");
    Node na[10];
    Edge e(&n);
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        e.here()->add(&na[i]);
        e.move();
    }

    Edge en(&n);
    std::string tmp;
    en.begin();
    for (int i = 0; i < 10; i++)
    {
        tmp += en.info();
        en.move();
    }
    return tmp;
}

// undo
std::string EdgeTest::travel_node_level_1()
{
    Node n = Node("main");
    Node na[10];
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::string(std::to_string(i)));
        n.add(&na[i]);
    }
    Edge e(&n);
    std::string res = "";
    for (size_t i = 0; i < e.source().edgeSize(); i++, e.next())
    {
        res += e.info();
    }
    return res;
}

void EdgeTest::TearDown()
{
}

