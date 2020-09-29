#include "edge_test.h"
#include "graph.h"

void EdgeTest::SetUp()
{
}

std::string EdgeTest::self_edge()
{
    Node n = Node("main");
    Node n1 = Node("destination");
    n.add(n1);
    Edge e = Edge(n);
    return e.info();
}

std::string EdgeTest::self_next()
{
    Node n = Node("main");
    Node na[10];
    for (int i = 10; i > 0; i--)
    {
        na[10 - i] = Node(std::to_string(i));
        n.add(na[10 - i]);
    }
    Edge e = Edge(n);
    std::string tmp;
    e.begin();
    for (size_t i = 0; i < e.here().edgeSize(); i++)
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
    Edge e = Edge(n);
    for (int i = 0; i < 10; i++)
    {
        na[i] = Node(std::to_string(i));
        e.here().add(na[i]);
        e.move();
    }

    Edge en = Edge(n);
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
        n.add(na[i]);
    }
    Edge e = Edge(n);
    std::string res = "";
    for (size_t i = 0; i < e.source().edgeSize(); i++, e.next())
    {
        res += e.info();
    }
    return res;
}

std::string EdgeTest::travel_node_level_2() {
    Node n = Node("main");
    Node na[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            na[i][j] = Node(std::string(std::to_string(i)) + std::string(std::to_string(j)));

            if (j == 0)
            {
                n.add(na[i][j]);
            }
            else 
            {
                na[i][0].add(na[i][j]);
            }
        }
    }
    Edge e = Edge(n);
    std::stack<Node*> stk;
    std::string tmp;
    e.begin();
    for (size_t i = 0; i < e.here().edgeSize(); i++)
    {
        tmp += e.info();
        stk.push(&e.to());
        e.next();
    }
    while (!stk.empty())
    {
        Node* tmp_n = stk.top();
        Edge en = Edge(*tmp_n);
        stk.pop();
        for (size_t i = 0; i < en.here().edgeSize(); i++)
        {
            tmp += en.info();
            en.next();
        }
    }
    return tmp;
}

std::string EdgeTest::travel_node_level_n()
{
    Node n = Node("main");
    Node na[2][2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                na[i][j][k] = Node(std::to_string(i) + std::to_string(j) + std::to_string(k));
            }
        }
    }
    // main 
    // 000     001
    // 010 011 100 101 
    // 110         111
    n.add(na[0][0][0]);
    n.add(na[0][0][1]);
    na[0][0][0].add(na[0][1][0]);
    na[0][0][0].add(na[0][1][1]);
    na[0][0][1].add(na[1][0][0]);
    na[0][0][1].add(na[1][0][1]);
    na[0][1][0].add(na[1][1][0]);
    na[1][0][1].add(na[1][1][1]);

    Edge e = Edge(n);
    std::string tmp;
    std::queue<Node*> que;
    que.push(&e.to());
    tmp += e.info();

    e.next();
    que.push(&e.to());
    tmp += e.info();

    while (!que.empty())
    {
        Edge en = Edge(*que.front());
        que.pop();
        en.begin();
        for (size_t i = 0; i < en.here().edgeSize(); i++)
        {
            tmp += en.info();
            que.push(&en.to());
            en.next();
        }
    }
    return tmp;
}

void EdgeTest::TearDown()
{
}

