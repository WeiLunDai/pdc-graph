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
    delete(node);
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
void Node::add(Node& dest)
{
    if ( !isTo(dest) )
    {
        node->_to.push_back(
                std::shared_ptr<Node>(new Node(dest.info())));
    }
}

void Node::del(Node& dest)
{
    begin();
    for (size_t i = 0; i < edgeSize(); i++, next())
    {
        if (to() == dest)
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

bool Node::isTo(Node& target)
{
    for (auto it = node->_to.begin();
            it != node->_to.end(); it++)
    {
        if ( **it == target )
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

Node& Node::to()
{
    // Node has no edge will to itself
    if (node->_to.size() == 0)
        return *this;

    if (node->_now_at >= node->_to.size())
        node->_now_at = 0;

    return *node->_to.at(node->_now_at);
}
void Node::next()
{
    if (++(node->_now_at) >= node->_to.size())
        node->_now_at = 0;
}

/*-------------*/

// init:
Edge::Edge(Node& ref) :
    edge(new _edge())
{
    edge->_source = &ref;
    edge->_destination = &ref.to();
    edge->_info = source().info() + "->" + dest().info() + "\n"; 
}

Edge::~Edge()
{
    delete(edge);
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
    return edge->_info;
}

bool Edge::operator==(Edge& e)
{
    return here() == e.here() || to() == e.to();
}

bool Edge::operator!=(Edge& e)
{
    return !(*this == e);
}

// selector:
Node& Edge::here()
{
    return *edge->_source;
}

void Edge::begin()
{
    edge->_source->begin();
}

Node& Edge::to()
{
    return *edge->_destination;
}

void Edge::next()
{
    edge->_source->next();
    edge->_destination = &edge->_source->to();
    edge->_info = source().info() + "->" + dest().info() + "\n"; 
}

// edit:
void Edge::move()
{
    edge->_source = &here().to();
    edge->_destination = &here().to();
    edge->_info = source().info() + "->" + dest().info() + "\n";
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
    graph->_info = ref.graph->_info;
    graph->nodes = ref.graph->nodes;
    graph->stk = ref.graph->stk;
}

Graph::Graph(GraphTable gt) :
    graph(new _graph())
{
    // node dict
    std::set<std::string> tmp;
    for (auto it = gt.begin();
            it != gt.end(); it++)
    {
        tmp.insert(it->first);
        tmp.insert(it->second);
    }

    // create node by dict
    for (auto it = tmp.begin();
            it != tmp.end(); it++) 
    {
        graph->nodes.push_back(new Node(*it));
    }

    // add relation
    for (auto it = gt.begin();
            it != gt.end(); it++)
    {
        Node n = Node(it->first);
        Node* tmp = find(n);
        if ( tmp != nullptr )
        {
            Node nd = Node(it->second);
            Node* new_n = find(nd);
            tmp->add(*new_n);
        }
    }
    // Since gt has dynamic allocation
}

Graph::~Graph()
{
    // TODO
    // !!RECHECK MEMORY LEAKAGE!!
    // for (NodeRefIt it = graph->nodes.begin();
    //         it != graph->nodes.end(); it++)
    // {
    //     delete(*it);
    // }
    delete(graph);
}

Graph& Graph::operator=(const Graph& rhs)
{
    graph->_info.assign(rhs.graph->_info);
    graph->nodes.assign(rhs.graph->nodes.begin(), rhs.graph->nodes.end());
    //graph->stk = rhs.graph->stk;

    return *this;
}

// info:
//
// if no found return nullptr
Node* Graph::find(Node& target)
{
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == target)
            return *it;
    }
    return nullptr;
}

// if no found return nullptr
Edge* Graph::find(Edge& edge)
{
    Node* src = find(edge.here());
    if (src == nullptr)
    {
        return nullptr;
    }
    else
    {
        for (size_t i = 0; i < src->edgeSize(); i++, src->next())
        {
            if (src->isTo(edge.to()))
            {
                // static Edge for return reference
                static Edge local_edge = Edge(*src);
                return &local_edge;
            }
        }
    }
    return nullptr;
}

Info Graph::info()
{
    graph->_info = "";
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        // set being for test
        (**it).begin();
        Edge tmp = Edge(**it);

        // if no edge, then only return name and "\n"
        if (tmp.source().edgeSize() == 0)
        {
            graph->_info += tmp.here().info() + "\n";
        }
        else
        {
            for (size_t i = 0; i < tmp.source().edgeSize(); i++)
            {
                graph->_info += tmp.info();
                tmp.next();
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

    for (NodeRefIt it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        count += (*it)->edgeSize();
    }

    return count;
}

void Graph::next()
{
    // next loop
    if (graph->stk.empty())
    {
        for (auto it = graph->nodes.begin();
                it != graph->nodes.end(); it++)
        {
            graph->stk.push(*it);
        }
    }

    // local edge remain iteration state
    static Edge local_edge = Edge( *graph->stk.top() );
    graph->stk.pop();
    for (size_t i = 0; i < local_edge.here().edgeSize();
            i++, local_edge.next())
    {
        graph->stk.push( &local_edge.to() );
    }
}

// edit:
// add the node and subnode
void Graph::add(Node& node)
{
    Node *tmp;
    if ( find(node) == nullptr )
    {
        tmp = new Node(node.info());
        graph->nodes.push_back(tmp);
    }
    // **We take this action into account is according to
    // our constructor by gt
    // add subnode
    for (size_t i = 0; i < node.edgeSize(); i++)
    {
        add(node.to());
        node.next();
    }
}

// add only this edge
void Graph::add(Edge& edge)
{
    Node* src_tmp = find(edge.here());
    Node* dest_tmp = find(edge.to());
    if (!src_tmp)
        add(edge.here());

    if (!dest_tmp)
        add(edge.to());

    src_tmp = find(edge.here());
    dest_tmp = find(edge.to());
    src_tmp->add(*dest_tmp);
}

// del node include subnode
bool Graph::del(Node& node)
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

    NodeRefIt tmp;
    for (auto it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == node)
        {
            tmp = it;
            status = true;
        }
    }
    if (status)
        graph->nodes.erase(tmp);

    return status;
}

bool Graph::del(Edge& edge)
{
    Node* tmp = find(edge.here());
    if (tmp == nullptr)
        return false;

    for (size_t i = 0; i < tmp->edgeSize(); i++, tmp->next())
    {
        if ( tmp->isTo(edge.to()) )
        {
            tmp->del(edge.to());
            return true;
        }
    }
    return false;
}

// generate a clone of graph by BFS
Graph& Graph::breathFirstSearch(Node& node)
{
    static std::queue<Node*> que;
    size_t edge_num = 0;

    // internal item
    static Graph b_travel;
    // turn on flag for auto relax memory
    b_travel.gt_alloc = true;


    Node* o_start = find(node);
    Node* new_node;
    if (o_start != nullptr)
        que.push(o_start);

    while(!que.empty())
    {
        // front will be parent in this run
        if ( b_travel.find(*que.front()) == nullptr )
        {
            new_node = new Node(que.front()->info());
            b_travel.add(*new_node);
        }

        // add all edge which is not in graph
        o_start = que.front();
        edge_num = 0;
        while (edge_num < o_start->edgeSize())
        {
            if ( b_travel.find(o_start->to()) == nullptr )
            {
                Node* parent = b_travel.find(*o_start);

                new_node = new Node(o_start->to().info());
                parent->add(*new_node);
                b_travel.add(*new_node);

                que.push( &o_start->to() );
            }
            edge_num++;
            o_start->next();
        }
        que.pop();

    }
    return b_travel;
}

// generate a clone of grapn by DFS
Graph& Graph::depthFirstSearch(Node& node)
{
    static std::stack<Node*> stk;
    size_t edge_num = 0;

    // internal item
    static Graph d_travel;
    // turn on flag for auto relax memory
    d_travel.gt_alloc = true;

    Node* o_start = find(node);
    Node* new_node;
    if (o_start != nullptr)
        stk.push(o_start);

    while(!stk.empty())
    {
        // top is parent
        if ( d_travel.find(*stk.top()) == nullptr )
        {
            new_node = new Node(stk.top()->info());
            d_travel.add(*new_node);
        }

        // check child
        // if not in graph, then push and reset edge_num for new parent
        // if in graph, plus edge_num
        o_start = stk.top();
        if ( d_travel.find(o_start->to()) == nullptr )
        {
            Node* parent = d_travel.find(*o_start);

            new_node = new Node(o_start->to().info());
            parent->add(*new_node);
            d_travel.add(*new_node);

            stk.push( &o_start->to() );
            edge_num = 0;
        }
        else
            edge_num++;

        o_start->next();

        // no more child can be add to graph
        if (edge_num >= o_start->edgeSize())
            stk.pop();

    }
    return d_travel;
}

void Graph::exportPngByte()
{
    GVC_t *gvc;
    Agraph_t *G;
    int tmp_size = 256;
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
            strncpy(tmp, (*it)->to().info().c_str(), tmp_size);
            n2 = agnode(G, tmp, false);
            agedge(G, n1, n2, 0, true);
            (*it)->next();
        }
    }

    gvLayout(gvc, G, "dot");

    strncpy(tmp, "title.png", 256);
    FILE *fp_png = fopen(tmp, "w");
    //gvRender(gvc, G, "png", fp_png);
    char* result = tmp;
    unsigned int length;
    gvRenderData(gvc, G, "png", &result, &length);

    fwrite(result, length, 1, fp_png);

    fclose(fp_png);

    // memcpy(buf, result, length);
    // *size = length;
    
    gvFreeLayout(gvc, G);
    agclose(G);
    gvFreeContext(gvc);
}

