#include "node_test.h"
#include "graph.h"

void NodeTest::SetUp()
{
}

std::string NodeTest::self_name()
{
    Node n = Node("I'm a Node");
    return n.info();
}

std::string NodeTest::self_size()
{
    Node n = Node("size");
    Node na[10];
    std::string info;
    info += std::to_string(n.edgeSize());
    for (size_t i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
        info += std::to_string(n.edgeSize());
    }
    return info;
}

std::string NodeTest::self_isTo()
{
    Node n = Node("main");
    Node n1 = Node("hello");
    std::string info;
    info += std::to_string(n.isTo(&n1));
    n.add(&n1);
    info += std::to_string(n.isTo(&n1));
    return info;
}

std::string NodeTest::self_next()
{
    Node n = Node("main");
    Node na[10];
    std::string info;
    for (size_t i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
        n.next();
        info += n.to()->info();
    }

    return info;
}

std::string NodeTest::self_to_zero()
{
    Node n = Node("main");
    return n.to()->info();
}

std::string NodeTest::add_one_node()
{
    Node n = Node("main");
    Node n1 = Node("new node");
    n.add(&n1);
    return n.to()->info();
}

std::string NodeTest::add_more_node()
{
    Node n1;
    Node na[10];
    std::string tmp;
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n1.add(&na[i]);
        n1.next();
        tmp += n1.to()->info();
    }
    return tmp;
}

std::string NodeTest::del_one_node()
{
    Node n = Node("main");
    Node na[10];
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
    }
    n.del(&na[5]);
    std::string info;
    n.begin();
    for (size_t i = 0; i < n.edgeSize(); i++)
    {
        info += n.to()->info();
        n.next();
    }
    return info;
}

std::string NodeTest::del_more_node()
{
    Node n = Node("main");
    Node na[10];
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        n.add(&na[i]);
    }
    for (int i = 3; i < 9; i++)
    {
        n.del(&na[i]);
    }
    std::string info;
    n.begin();
    for (size_t i = 0; i < n.edgeSize(); i++)
    {
        info += n.to()->info();
        n.next();
    }
    return info;
}

void NodeTest::TearDown()
{
}
