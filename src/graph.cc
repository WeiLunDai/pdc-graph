#include "graph.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <cassert>
#include <sstream>
#include <vector>
#include <queue>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/*---------------*/

Node::Node() :
    node(new _node())
{
    node->_info = "";
    node->_now_at = 0;
}

Node::Node(Info name) :
    node(new _node())
{
    node->_info.assign(name);
    node->_now_at = 0;
}

Node::Node(const Node& ref) :
    node(new _node())
{
    node->_info.assign(ref.node->_info);
    node->_to.assign(ref.node->_to.begin(), ref.node->_to.end());
    node->_now_at = ref.node->_now_at;
}

Node::~Node()
{
}

const Node& Node::operator=(const Node& rhs) const
{
    node->_info.assign(rhs.node->_info);
    node->_to.assign(rhs.node->_to.begin(), rhs.node->_to.end());

    node->_now_at = rhs.node->_now_at;
    return *this;
}

bool Node::operator==(const Node& rhs) const
{
    return node->_info == rhs.node->_info;
}

bool Node::operator!=(Node& rhs)
{
    return !(*this==rhs);
}

// edit:
void Node::add(Node* dest)
{
    if ( !isTo(dest) )
    {
        node->_to.push_back(
                std::shared_ptr<Node>(new Node(*dest)));
    }
}

void Node::del(Node* dest)
{
    begin();
    for (size_t i = 0; i < edgeSize(); i++, next())
    {
        if (*to() == *dest)
        {
            node->_to.erase( node->_to.begin() + node->_now_at );
            node->_now_at = 0;
        }
    }
}

// info:
Info Node::info() const
{
    return node->_info;
}

bool Node::isTo(Node* target)
{
    for (auto it = node->_to.begin();
            it != node->_to.end(); it++)
    {
        if ( **it == *target )
            return true;
    }
    return false;
}

size_t Node::edgeSize() const
{
    return node->_to.size();
}

// selector:
void Node::begin()
{
    node->_now_at = 0;
}

Node* Node::to()
{
    // Node has no edge will to itself
    if (node->_to.size() == 0)
        return this;

    if (node->_now_at >= node->_to.size())
        node->_now_at = 0;

    return node->_to.at(node->_now_at).get();
}
void Node::next()
{
    if (++(node->_now_at) >= node->_to.size())
        node->_now_at = 0;
}

/*-------------*/

// init:
Edge::Edge(Node* ref) :
    edge(new _edge())
{
    edge->_source = ref;
    edge->_destination = ref->to();
    edge->_info = source().info() + "->" + dest().info() + "\n"; 
}

Edge::~Edge()
{
}

// info:
const Node& Edge::source() const
{
    return *edge->_source;
}

const Node& Edge::dest() const
{
    return *edge->_destination;
}

Info Edge::info()
{
    edge->_info = source().info() + "->" + dest().info() + "\n"; 
    return edge->_info;
}

bool Edge::operator==(Edge& e)
{
    return *here() == *e.here() || *to() == *e.to();
}

bool Edge::operator!=(Edge& e)
{
    return !(*this == e);
}

// selector:
Node* Edge::here()
{
    return edge->_source;
}

void Edge::begin()
{
    edge->_source->begin();
}

Node* Edge::to()
{
    return edge->_destination;
}

void Edge::next()
{
    edge->_source->next();
    edge->_destination = edge->_source->to();
}

// edit:
void Edge::move()
{
    edge->_source = here()->to();
    edge->_destination = here()->to();
}

/*-------------*/

// init:
Graph::Graph() :
    graph(new _graph())
{
}

Graph::Graph(const Graph& ref) :
    graph(new _graph())
{
    graph->_info.assign(ref.graph->_info);
    graph->nodes.assign(ref.graph->nodes.begin(), ref.graph->nodes.end());
}

Graph::Graph(GraphTable& gt) :
    graph(new _graph())
{
    // node dict
    std::set<std::string> dict;
    for (auto it = gt.begin(); it != gt.end(); it++)
    {
        add(it->first, it->second);
    }
}

Graph::~Graph()
{
}

Graph& Graph::operator=(const Graph& rhs)
{
    graph->_info.assign(rhs.graph->_info);
    graph->nodes.assign(rhs.graph->nodes.begin(), rhs.graph->nodes.end());

    return *this;
}

// info:
//
// if no found return nullptr
Node* Graph::find(Node* target)
{
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == *target)
            return (*it).get();
    }
    return nullptr;
}

Node* Graph::find(Info info)
{
    Node tmp = Node(info);
    return find(&tmp);
}

// if no found return nullptr
Edge* Graph::find(Edge* edge)
{
    Node* src = find(edge->here());
    if (src == nullptr)
    {
        return nullptr;
    }
    else
    {
        for (size_t i = 0; i < src->edgeSize(); i++, src->next())
        {
            if (src->isTo( edge->to() ))
            {
                // static Edge for return reference
                static std::unique_ptr<Edge>local_edge(new Edge(src));
                return local_edge.get();
            }
        }
    }
    return nullptr;
}

Edge* Graph::find(Info src_info, Info dest_info)
{
    Node src_e(src_info);
    Node dest_e(dest_info);
    src_e.add(&dest_e);
    Edge ed(&src_e);

    return find(&ed);
}

Info Graph::info()
{
    graph->_info = "";
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        // set being for test
        (*it)->begin();

        // if no edge, then only return name and "\n"
        if ((*it)->edgeSize() == 0)
        {
            graph->_info += (*it)->info() + "\n";
        }
        else
        {
            for (size_t i = 0; i < (*it)->edgeSize(); i++)
            {
                Edge tmp(it->get());
                graph->_info += tmp.info();

                (*it)->next();
            }
        }
    }
    return graph->_info;
}

size_t Graph::nodeSize()
{
    return graph->nodes.size();
}

size_t Graph::edgeSize()
{
    size_t count = 0;

    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        count += (*it)->edgeSize();
    }

    return count;
}

// void Graph::next()
// {
//     // next loop
//     if (graph->stk.empty())
//     {
//         for (auto it = graph->nodes.begin();
//                 it != graph->nodes.end(); it++)
//         {
//             graph->stk.push(&**it);
//         }
//     }
//
//     // local edge remain iteration state
//     static Edge local_edge = Edge( *graph->stk.top() );
//     graph->stk.pop();
//     for (size_t i = 0; i < local_edge.here()->edgeSize();
//             i++, local_edge.next())
//     {
//         graph->stk.push( local_edge.to() );
//     }
// }

// edit:
// add the node and subnode
void Graph::add(Node* node)
{
    if ( find(node) == nullptr )
    {
        graph->nodes.push_back(
                std::shared_ptr<Node>(new Node(node->info())));
    }
    // **We take this action into account is according to
    // our constructor by gt
    // add subnode
    for (size_t i = 0; i < node->edgeSize(); i++)
    {
        add(node->to());
        node->next();
    }
}

void Graph::add(Info info)
{
    Node node(info);
    add(&node);
}

// add only this edge
void Graph::add(Edge* edge)
{
    Node* src_tmp = find(edge->here());
    Node* dest_tmp = find(edge->to());
    if (!src_tmp)
        add(edge->here());

    if (!dest_tmp)
        add(edge->to());

    src_tmp = find(edge->here());
    dest_tmp = find(edge->to());
    src_tmp->add(dest_tmp);
}

void Graph::add(Info src_info, Info dest_info)
{
    Node src_e(src_info);
    Node dest_e(dest_info);
    src_e.add(&dest_e);
    Edge ed(&src_e);

    add(&ed);
}

// del node include subnode
bool Graph::del(Node* node)
{
    bool status = false;
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if ( (*it)->isTo(node) )
        {
            (*it)->del(node);
        }
    }

    int tmp;
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == *node)
        {
            tmp = it - graph->nodes.begin();
            status = true;
        }
    }
    if (status)
        graph->nodes.erase(graph->nodes.begin() + tmp);

    return status;
}

bool Graph::del(Info info)
{
    Node node(info);
    return del(&node);
}

bool Graph::del(Edge* edge)
{
    Node* tmp = find(edge->here());
    if (tmp == nullptr)
        return false;

    for (size_t i = 0; i < tmp->edgeSize(); i++, tmp->next())
    {
        if ( tmp->isTo(edge->to()) )
        {
            tmp->del(edge->to());
            return true;
        }
    }
    return false;
}

bool Graph::del(Info src_info, Info dest_info)
{
    Node src_e(src_info);
    Node dest_e(dest_info);
    src_e.add(&dest_e);
    Edge ed(&src_e);

    return del(&ed);
}

// generate a clone of graph by BFS
Graph* Graph::breathFirstSearch(Node* node)
{
    std::queue<Node*> que;
    size_t edge_num = 0;

    // internal item
    static std::shared_ptr<Graph> travel;
    travel.reset();
    travel = std::shared_ptr<Graph>(new Graph());
    // turn on flag for auto relax memory

    Node* start = find(node);
    if (start != nullptr)
        que.push(start);

    while(!que.empty())
    {
        travel->add(que.front()->info());

        // add all edge which is not in graph
        start = que.front();
        edge_num = 0;
        while (edge_num < start->edgeSize())
        {
            if ( travel->find(start->to()) == nullptr )
            {
                travel->add(
                        travel->find(start)->info(),
                        start->to()->info());

                que.push( find(start->to()) );
            }
            edge_num++;
            start->next();
        }
        que.pop();

    }
    return travel.get();
}

Graph* Graph::breathFirstSearch(Info info)
{
    Node n(info);
    return breathFirstSearch(&n);
}

// generate a clone of grapn by DFS
Graph* Graph::depthFirstSearch(Node* node)
{
    std::stack<Node*> stk;
    size_t edge_num = 0;

    // internal item
    static std::shared_ptr<Graph> travel;
    travel.reset();
    travel = std::shared_ptr<Graph>(new Graph());
    // turn on flag for auto relax memory

    Node* start = find(node);
    if (start != nullptr)
        stk.push(start);

    while(!stk.empty())
    {
        // top is parent
        travel->add(stk.top()->info());

        // check child
        // if not in graph, then push and reset edge_num for new parent
        // if in graph, plus edge_num
        start = stk.top();
        if ( travel->find(start->to()) == nullptr )
        {
            travel->add(
                    travel->find(start)->info(),
                    start->to()->info());

            stk.push( find(start->to()) );
            edge_num = 0;
        }
        else
            edge_num++;

        start->next();

        // no more child can be add to graph
        if (edge_num >= start->edgeSize())
            stk.pop();

    }
    return travel.get();
}

Graph* Graph::depthFirstSearch(Info info)
{
    Node n(info);
    return depthFirstSearch(&n);
}

void Graph::exportPng()
{
    GVC_t *gvc;
    Agraph_t *G;
    constexpr int tmp_size = 256;
    char tmp[tmp_size];

    gvc = gvContext();

    strncpy(tmp, "title", tmp_size);
    G = agopen(tmp, Agdirected, 0);

    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        strncpy(tmp, (*it)->info().c_str(), tmp_size);
        agnode(G, tmp, true);
    }

    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {

        // loop for edge to 

        Agnode_t *n1, *n2;
        strncpy(tmp, (*it)->info().c_str(), tmp_size);
        n1 = agnode(G, tmp, false);

        for (size_t i = 0; i < (*it)->edgeSize(); i++)
        {
            strncpy(tmp, (*it)->to()->info().c_str(), tmp_size);
            n2 = agnode(G, tmp, false);
            agedge(G, n1, n2, 0, true);
            (*it)->next();
        }
    }

    gvLayout(gvc, G, "dot");

    strncpy(tmp, "title.png", tmp_size);
    FILE *fp_png = fopen(tmp, "w");
    //gvRender(gvc, G, "png", fp_png);
    char* result = tmp;
    unsigned int length;
    gvRenderData(gvc, G, "png", &result, &length);

    fwrite(result, length, 1, fp_png);

    fclose(fp_png);

    gvFreeLayout(gvc, G);
    agclose(G);
    gvFreeContext(gvc);
}

