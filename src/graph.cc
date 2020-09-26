#include "graph.h"
#include <iostream>
#include <set>
#include <cassert>
#include <vector>

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

// Node::Node(Node& ref) :
//     node(new _node())
// {
//     node->_info   = ref.node->_info;
//     node->_to     = ref.node->_to;
//     node->_now_at = ref.node->_now_at;
// }

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

// bool Node::operator==(Node& rhs)
// {
//     return node->_info == rhs.node->_info;
// }

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
    if ( isTo(dest) )
    {
        for (size_t i = 0; i < edgeSize(); i++, next())
        {
            if (to() == dest)
            {
                node->_to.erase( node->_to.begin() + node->_now_at );
                node->_now_at = 0;
                // node->_to.erase(node->_now_at);
                // node->_now_at = node->_to.begin();
            }
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
    // for (size_t i = 0; i < edgeSize(); i++, next())
    // {
    //     if (to() == node)
    //         return true;
    // }
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
    if (node->_to.size() == 0)
        return *this;

    if (node->_now_at >= node->_to.size())
        node->_now_at = 0;
    // if (node->_now_at == node->_to.end())
    //     node->_now_at = node->_to.begin();

    // Node* n = *node->_now_at;
    return *node->_to.at(node->_now_at);
    //return (*(*(node->_now_at)));
}
void Node::next()
{
    if (++(node->_now_at) >= node->_to.size())
        node->_now_at = 0;
    // if (++(node->_now_at) == node->_to.end() )
    //     node->_now_at = node->_to.begin();
}

// Node::Node(c_label info) : info(info) {};

// Node::Node(Node& node)
// {
//     this->info = node.get_info();
// };

// clone a new same node 
// Node* Node::clone()
// {
//     return new Node(this->get_info());
// };

// Node& Node::operator=(Node& node)
// {
//     this->info = node.get_info();
//     return *this;
// }

// get info about node
// c_label Node::get_info() const
// {
//     return info.c_str();
// }

/*-------------*/

// init Edge with basic c_label
// Edge::Edge(c_label source, c_label dest) :
//     info(""), source(new Node(source)),dest(new Node(dest)) {};

// init Edge with other already allocated node
// Edge::Edge(Node* source, Node* dest) :
//     info(""), source(source), dest(dest) {};

// Edge::Edge(Edge& e)
// {
//    edge = std::make_pair(e.get_src(), e.get_dst());
// }


// clone a new Edge
// Edge* Edge::clone()
// {
//     return new Edge(source->get_info(), dest->get_info());
// }

// Node* Edge::get_src()
// {
//     return edge.first;
// };
//
// Node* Edge::get_dst()
// {
//     return edge.second;
// };

// get info about Edge
// c_label Edge::get_info()
// {
//     info = std::string(source->get_info()) +
//         " -> " +
//         std::string(dest->get_info());
//     return info.c_str();
// }

// simplify get_node.get_info method
// c_label Edge::get_src_info() const
// {
//     return source->get_info();
// };

// simplify get_node.get_info method
// c_label Edge::get_dst_info() const
// {
//     return dest->get_info();
// };


// init:
Edge::Edge(Node& ref) :
    edge(new _edge())
{
    edge->_source = &ref;
    edge->_destination = &ref.to();
    edge->_info = source().info() + "->" + dest().info() + "\n"; 
}

// Edge::Edge(Edge& e) :
//     edge(new _edge())
// {
//     edge->_source = e.edge->_source;
//     edge->_destination= e.edge->_destination;
//     edge->_info = e.edge->_info;
// }

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
Graph::Graph()
{
}

Graph::Graph(GraphTable gt)
{
    graph = new _graph();
    std::set<std::string> tmp;
    for (GraphTable::iterator it = gt.begin();
            it != gt.end(); it++)
    {
        tmp.insert(it->first);
        tmp.insert(it->second);
    }

    for (std::set<std::string>::iterator it = tmp.begin();
            it != tmp.end(); it++) 
    {
        graph->nodes.push_back(new Node(*it));
    }

    for (GraphTable::iterator it = gt.begin();
            it != gt.end(); it++)
    {
        Node n = Node(it->first);
        Node* tmp = find(n);
        if ( tmp != nullptr )
        {
            Node* new_n = new Node(it->second);
            tmp->add(*new_n);
        }
    }

    graph->travel_graph = new Graph();
    // graph->edge = **graph->nodes.begin();
}

Graph::~Graph()
{
    delete(graph);
}

// info:
// Node* Graph::find_sub(Node& source, Node& target)
// {
//     Edge e = Edge(source);
//
//     for (size_t i = 0;
//             i < e.here().edgeSize();
//             i++, e.next())
//     {
//         if (e.dest() == target) return &e.to();
//     }
//
//     for (size_t i = 0;
//             i < e.here().edgeSize();
//             i++, e.next())
//     {
//         find_sub(e.to(), target);
//     }
//
//     return nullptr;
// }

Node* Graph::find(Node& target)
{
    for (std::vector<Node*>::iterator it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == target)
            return *it;
        //return find_sub(**it, target);
    }
    return nullptr;
}

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
                graph->edge = new Edge(*src);
                return graph->edge;
                //return &edge;
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
        Edge tmp = Edge(**it);
        for (size_t i = 0; i < tmp.source().edgeSize(); i++, tmp.here().next())
        {
            graph->_info += tmp.info();
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

// Node& Graph::nowAt()
// {
//     return graph->edge.here();
// }
//
// Node& Graph::to()
// {
//     return graph->edge.to();
// }

void Graph::next()
{
    if (graph->stk.empty())
    {
        for (std::vector<Node*>::iterator it = graph->nodes.begin();
                it != graph->nodes.end(); it++)
        {
            graph->stk.push(*it);
        }
    }

    static Edge edge = Edge( *graph->stk.top() );
    graph->stk.pop();
    for (size_t i = 0;
            i < edge.here().edgeSize();
            i++, edge.next())
    {
        graph->stk.push( &edge.to() );
    }
}

// edit:
bool Graph::add(Node& node)
{
    if ( find(node) != nullptr )
    {
        graph->nodes.push_back(&node);
        return true;
    }
    return false;
}

bool Graph::add(Edge& edge)
{
    Node* tmp = find(edge.here());
    if (!tmp)
        add(edge.here());
    tmp = find(edge.here());
    for (size_t i = 0; i < edge.here().edgeSize(); i++, edge.next())
    {
        tmp->add(edge.to());
    }
    return true;
}

bool Graph::del(Node& node)
{
    for (std::vector<Node*>::iterator it = graph->nodes.begin();
            it != graph->nodes.end(); it++)
    {
        if (**it == node)
        {
            Node* tmp = *it;
            graph->nodes.erase(it);
            delete(tmp);
            return true;
        }
        //return find_sub(**it, target);
    }
    return false;
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

bool Graph::breathFirstSearch(Node& node)
{
    static std::queue<Node*> que;

    Node* tmp = find(node);
    que.push(tmp);

    while (!que.empty())
    {
        Edge e = Edge( *que.front() );
        for (size_t i = 0; i < tmp->edgeSize(); i++, e.next())
        {
            if ( graph->travel_graph->find(e.to()) == nullptr )
            {
                graph->travel_graph->add(e);
                que.push(&e.to());
            }

        }
    }
    std::cout << graph->travel_graph->info();
    return true;
}

bool Graph::depthFirstSearch(Node& node)
{
    static std::stack<Node*> stk;

    Node* tmp = find(node);
    stk.push(tmp);

    while (!stk.empty())
    {
        Edge e = Edge( *stk.top() );
        for (size_t i = 0; i < tmp->edgeSize(); i++, e.next())
        {
            if ( graph->travel_graph->find(e.to()) == nullptr )
            {
                graph->travel_graph->add(e);
                stk.push(&e.to());
            }

        }
    }
    std::cout << graph->travel_graph->info();
    return true;
}

// Graph::Graph() :
//     info(""), node_cache(), graph()
// {
// }
//
// // normally get Graph from here
// Graph::Graph(GraphTable table) :
//     info("")
// {
//     // travel table
//     for (GraphTable::iterator it = table.begin();
//             it != table.end(); it++)
//     {
//         add_edge(it->first.c_str(), it->second.c_str());
//     }
// }
//
// Graph::~Graph()
// {
//     for (GraphBody::iterator it = graph.begin();
//             it != graph.end(); it++)
//     {
//         for (EdgeSet::iterator edge_it = it->second.begin();
//                 edge_it != it->second.end(); edge_it++)
//         {
//             delete(*edge_it);
//         }
//         //delete(it->first);
//     }
// }
//
// // only get edge info, no node info
// c_label Graph::get_info()
// {
//     info = "";
//     // travel edge
//     for (GraphBody::iterator it = graph.begin();
//             it != graph.end(); it++)
//     {
//         for (EdgeSet::iterator edge_it = it->second.begin();
//                 edge_it != it->second.end(); edge_it++)
//         {
//             info += (*edge_it)->get_info() + std::string("\n");
//         }
//     }
//     return info.c_str();
// }
//
// size_t Graph::size_node()
// {
//     return node_cache.size();
// }
//
// size_t Graph::size_edge()
// {
//     size_t accum = 0;
//     for (GraphBody::iterator it = graph.begin();
//             it != graph.end(); it++)
//     {
//         accum += (*it).second.size();
//     }
//     return accum;
// }
//
// Node* Graph::find_node(c_label name)
// {
//     NodeCache::iterator it = node_cache.find(name);
//     if ( it == node_cache.end())
//         return nullptr;
//
//     return it->second;
// }
//
// Edge* Graph::find_edge(c_label source, c_label dest)
// {
//     NodeCache::iterator node_it = node_cache.find(source);
//     // check source existence, since it is a index of edge
//     if ( node_it == node_cache.end() )
//         return nullptr;
//
//     // get EdgeSet
//     GraphBody::iterator graph_it = graph.find( node_it->second );
//
//     // travel EdgeSet
//     for ( EdgeSet::iterator edge_it = graph_it->second.begin();
//             edge_it != graph_it->second.end();
//             edge_it++)
//     {
//         if ( std::string((*edge_it)->get_dst_info()) == std::string(dest) )
//             return *edge_it;
//     }
//
//     return nullptr;
// }
//
// Node* Graph::add_node(c_label name)
// {
//     // check node existence
//     if ( find_node(name) == nullptr )
//     {
//         // give new node
//         Node* temp = new Node(name);
//         node_cache.insert( std::make_pair(name, temp) );
//         graph.insert( std::make_pair(temp, EdgeSet()));
//         return temp;
//     }
//     return nullptr;
// }
//
// Edge* Graph::add_edge(c_label source, c_label dest)
// {
//     // edge imply two node exist
//     // check those two node
//     // or add them to graph
//     Node* n_src = find_node(source);
//     Node* n_dst = find_node(dest);
//
//     if (n_src == nullptr)
//         n_src = add_node(source);
//
//     if (n_dst == nullptr)
//         n_dst = add_node(dest);
//
//     // check edge existence
//     if ( find_edge(source, dest) == nullptr )
//     {
//         Edge* temp = new Edge(source, dest);
//         GraphBody::iterator it = graph.find(n_src);
//         it->second.insert(temp);
//         return temp;
//     }
//
//     return nullptr;
// }
//
// // not complete
// Graph* Graph::breadth_firsh_search(c_label name)
// {
//     Node* tmp = find_node(name);
//     if (tmp == nullptr)
//         return nullptr;
//
//     Edge start_point = Edge(tmp, tmp);
//     Graph *g = new Graph();
//
//     std::queue<Edge*> que;
//     que.push(&start_point);
//
//     while( !que.empty() )
//     {
//         Node *n_tmp;
//         Edge *e_tmp = que.front();
//         GraphBody::iterator it;
//         c_label new_src_node = e_tmp->get_dst_info();
//
//         if ( g->find_node( new_src_node ) == nullptr)
//         {
//             if (e_tmp->get_dst_info() != start_point.get_src_info())
//                 g->add_edge(e_tmp->get_src_info(), e_tmp->get_dst_info());
//
//             que.pop();
//
//             n_tmp = find_node( new_src_node );
//             assert(n_tmp != nullptr);
//             it = graph.find( n_tmp );
//
//             for (EdgeSet::iterator edge_it = it->second.begin();
//                     edge_it != it->second.end(); edge_it++)
//             {
//                 c_label new_dest_node = (*edge_it)->get_dst_info();
//                 if ( g->find_node( new_dest_node ) == nullptr )
//                     que.push( *edge_it );
//             }
//         }
//         else
//         {
//             que.pop();
//         }
//     }
//
//     return g;
// }
//
// Graph* Graph::depth_firsh_search(c_label name)
// {
//     Node* tmp = find_node(name);
//     if (tmp == nullptr)
//         return nullptr;
//
//     Edge start_point = Edge(tmp, tmp);
//     Graph *g = new Graph();
//
//     std::stack<Edge*> stk;
//     stk.push(&start_point);
//
//     while( !stk.empty() )
//     {
//         Node *n_tmp;
//         Edge *e_tmp = stk.top();
//         GraphBody::iterator it;
//         c_label new_src_node = e_tmp->get_dst_info();
//
//         if ( g->find_node( new_src_node ) == nullptr)
//         {
//             if (e_tmp->get_dst_info() != start_point.get_src_info())
//                 g->add_edge(e_tmp->get_src_info(), e_tmp->get_dst_info());
//
//             stk.pop();
//
//             n_tmp = find_node( new_src_node );
//             assert(n_tmp != nullptr);
//             it = graph.find( n_tmp );
//
//             for (EdgeSet::iterator edge_it = it->second.begin();
//                     edge_it != it->second.end(); edge_it++)
//             {
//                 c_label new_dest_node = (*edge_it)->get_dst_info();
//                 if ( g->find_node( new_dest_node ) == nullptr )
//                     stk.push( *edge_it );
//             }
//         }
//         else
//         {
//             stk.pop();
//         }
//     }
//
//
//     return g;
// }
//

/*--------------------*/

// Graph_test::Graph_test():
//     gt( { {"1", "2"}, {"1", "3"}, {"2", "4"},
//           {"2", "6"}, {"3", "4"}, {"3", "5"},
//           {"4", "6"}, {"5", "1"}, {"6", "5"}} ),
//     g(gt)
// {
//     std::cout << g.get_info() << std::endl;
//
//     Graph *bfs = g.breadth_firsh_search("2");
//     std::cout << bfs->get_info() << std::endl;
//     delete(bfs);
//     bfs = g.depth_firsh_search("2");
//     std::cout << bfs->get_info() << std::endl;
//     delete(bfs);
// };
