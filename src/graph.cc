#include "graph.h"
#include <cstring>
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
}

Node::Node(Info name) :
    node(new _node())
{
    node->_info   = name;
    node->_now_at = -1;
}

Node::Node(const Node& ref) :
    node(new _node())
{
    node->_info   = ref.node->_info;
    node->_to     = ref.node->_to;
    node->_now_at = ref.node->_now_at;
}

Node::~Node()
{
    delete(node);
}

const Node& Node::operator=(const Node& rhs) const
{
    node->_info   = rhs.node->_info;
    node->_to     = rhs.node->_to;
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
        node->_to.push_back(&dest);
}

void Node::del(Node& dest)
{
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

bool Node::isTo(Node& node)
{
    for (std::vector<Node*>::iterator it = this->node->_to.begin();
            it != this->node->_to.end(); it++)
    {
        if ( **it == node )
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
    for (GraphTable::iterator it = gt.begin();
            it != gt.end(); it++)
    {
        tmp.insert(it->first);
        tmp.insert(it->second);
    }

    // create node by dict
    for (std::set<std::string>::iterator it = tmp.begin();
            it != tmp.end(); it++) 
    {
        graph->nodes.push_back(new Node(*it));
    }

    // add relation
    for (GraphTable::iterator it = gt.begin();
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
    gt_alloc = true;
}

Graph::~Graph()
{
    if (gt_alloc)
    {
        for (std::vector<Node*>::iterator it = graph->nodes.begin();
                it != graph->nodes.end(); it++)
        {
            delete(*it);
        }
    }
    delete(graph);
}

Graph& Graph::operator=(const Graph& rhs)
{
    graph->_info = rhs.graph->_info;
    graph->nodes = rhs.graph->nodes;
    graph->stk = rhs.graph->stk;

    return *this;
}

// info:
//
// if no found return nullptr
Node* Graph::find(Node& target)
{
    for (std::vector<Node*>::iterator it = graph->nodes.begin();
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
    for (std::vector<Node*>::iterator it = graph->nodes.begin();
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

    for (std::vector<Node*>::iterator it = graph->nodes.begin();
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
        for (std::vector<Node*>::iterator it = graph->nodes.begin();
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
    if ( find(node) == nullptr )
    {
        graph->nodes.push_back(&node);
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
    Node* tmp = find(edge.here());
    if (!tmp)
        add(edge.here());
    tmp = find(edge.here());
    tmp->add(edge.to());
    add(edge.to());
}

// del node include subnode
bool Graph::del(Node& node)
{
    bool status = false;
    for (std::vector<Node*>::iterator it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if ( (*it)->isTo(node) )
        {
            (*it)->del(node);
        }

        if (**it == node)
        {
            graph->nodes.erase(it);
            status = true;
        }
    }
    return status;
}

bool Graph::del(Edge& edge)
{
    Node* tmp = find(edge.here());
    for (size_t i = 1; i < edge.here().edgeSize(); i++, edge.next())
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

void Graph::exportPngByte(char* buf, size_t* size)
{
    GVC_t *gvc;
    Agraph_t *G;
    int tmp_size = 256;
    char tmp[tmp_size];

    gvc = gvContext();

    strncpy(tmp, "title", tmp_size);
    G = agopen(tmp, Agdirected, 0);

    size_t count = 0;
    for (nodeRef it = graph->nodes.begin();
            it != graph->nodes.end() && count < graph->nodes.size();
            it++, count++)
    {
        strncpy(tmp, (*it)->info().c_str(), tmp_size);
        agnode(G, tmp, true);
    }

    count = 0;
    for (nodeRef it = graph->nodes.begin();
            it != graph->nodes.end() && count < graph->nodes.size();
            it++, count++)
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

    //strncpy(tmp, (std::string(filename) + ".png").c_str(), 256);
    FILE *fp_png = fopen(tmp, "w");
    //gvRender(gvc, G, "png", fp_png);
    char* result = tmp;
    unsigned int length;
    gvRenderData(gvc, G, "png", &result, &length);

    fwrite(result, length, 1, fp_png);

    memcpy(buf, result, length);
    *size = length;
    
    gvFreeLayout(gvc, G);
    agclose(G);
    gvFreeContext(gvc);
}

