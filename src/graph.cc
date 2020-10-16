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

Node::Node()
{
    _info = "";
    _now_at = 0;
}

Node::Node(Info name)
{
    _info.assign(name);
    _now_at = 0;
}

Node::Node(const Node& ref)
{
    _info.assign(ref._info);
    _to.assign(ref._to.begin(), ref._to.end());
    _now_at = ref._now_at;
}

Node::~Node()
{
}

const Node& Node::operator=(const Node& rhs) 
{
    _info.assign(rhs._info);
    _to.assign(rhs._to.begin(), rhs._to.end());

    _now_at = rhs._now_at;
    return *this;
}

bool Node::operator==(const Node& rhs) const
{
    return _info == rhs._info;
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
        _to.push_back(
                std::shared_ptr<Node>(new Node(*dest)));
    }
}

void Node::del(Node* dest)
{
    auto it = _to.begin();
    while (it != _to.end())
    {
        if ( *it->get() == *dest)
            it = _to.erase(it);
        else
            it++;
    }
    // begin();
    // for (size_t i = 0; i < edgeSize(); i++, next())
    // {
    //     if (*to() == *dest)
    //     {
    //         node->_to.erase( node->_to.begin() + node->_now_at );
    //         node->_now_at = 0;
    //     }
    // }
}

// info:
Info Node::info() const
{
    return _info;
}

bool Node::isTo(Node* target)
{
    for (auto &it : _to)
    {
        if ( *it == *target )
            return true;
    }
    return false;
}

size_t Node::edgeSize() const
{
    return _to.size();
}

// selector:
void Node::begin()
{
    _now_at = 0;
}

Node* Node::to()
{
    // Node has no edge will to itself
    if (_to.size() == 0)
        return this;

    if (_now_at >= _to.size())
        _now_at = 0;

    return _to.at(_now_at).get();
}
void Node::next()
{
    if (++(_now_at) >= _to.size())
        _now_at = 0;
}

/*-------------*/

// init:
Edge::Edge(Node* ref)
{
    _source = ref;
    _destination = ref->to();
    _info = source().info() + "->" + dest().info() + "\n"; 
}

Edge::~Edge()
{
}

// info:
const Node& Edge::source() const
{
    return *_source;
}

const Node& Edge::dest() const
{
    return *_destination;
}

Info Edge::info()
{
    _info = source().info() + "->" + dest().info() + "\n"; 
    return _info;
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
    return _source;
}

void Edge::begin()
{
    _source->begin();
}

Node* Edge::to()
{
    return _destination;
}

void Edge::next()
{
    _source->next();
    _destination = _source->to();
}

// edit:
void Edge::move()
{
    _source = here()->to();
    _destination = here()->to();
}

/*-------------*/

// init:
Graph::Graph()
{
}

Graph::Graph(const Graph& ref)
{
    _info.assign(ref._info);
    nodes.assign(ref.nodes.begin(), ref.nodes.end());
}

Graph::Graph(GraphTable& gt)
{
    // node dict
    for (auto &it : gt)
    {
        add(it.first, it.second);
    }
}

Graph::~Graph()
{
}

Graph& Graph::operator=(const Graph& rhs)
{
    _info.assign(rhs._info);
    nodes.assign(rhs.nodes.begin(), rhs.nodes.end());

    return *this;
}

// info:
//
// if no found return nullptr
Node* Graph::find(Node* target)
{
    for (auto &it : nodes)
    {
        if (*it == *target)
            return it.get();
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
    _info = "";
    for (auto &it : nodes)
    {
        // set being for test
        it->begin();

        // if no edge, then only return name and "\n"
        if (it->edgeSize() == 0)
        {
            _info += it->info() + "\n";
        }
        else
        {
            for (size_t i = 0; i < it->edgeSize(); i++)
            {
                Edge tmp(it.get());
                _info += tmp.info();

                it->next();
            }
        }
    }
    return _info;
}

size_t Graph::nodeSize()
{
    return nodes.size();
}

size_t Graph::edgeSize()
{
    size_t count = 0;

    for (auto &it : nodes)
    {
        count += it->edgeSize();
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
        nodes.push_back(
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
    for (auto &it : nodes)
    {
        if ( it->isTo(node) )
        {
            it->del(node);
        }
    }

    // int tmp;
    auto it = nodes.begin();
    while (it != nodes.end())
    {
        if (**it == *node)
        {
            it = nodes.erase(it);
            status = true;
        }
        else 
            it++;
    }

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
    constexpr int tmp_size = 256;
    char tmp[tmp_size];

    GVC_t *gvc = gvContext();
    Agraph_t *G = agopen(tmp, Agdirected, 0);

    strncpy(tmp, "title", tmp_size);

    for (auto &it : nodes)
    {
        strncpy(tmp, it->info().c_str(), tmp_size);
        agnode(G, tmp, true);
    }

    for (auto &it : nodes)
    {

        // loop for edge to 

        strncpy(tmp, it->info().c_str(), tmp_size);
        Agnode_t *n1 = agnode(G, tmp, false);

        for (size_t i = 0; i < it->edgeSize(); i++)
        {
            strncpy(tmp, it->to()->info().c_str(), tmp_size);
            Agnode_t *n2 = agnode(G, tmp, false);
            agedge(G, n1, n2, 0, true);
            it->next();
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
