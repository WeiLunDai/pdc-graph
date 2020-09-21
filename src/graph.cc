#include "graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <string>
#include <cassert>

/*---------------*/

Node::Node(c_label info) : info(info) {};

// Node::Node(Node& node)
// {
//     this->info = node.get_info();
// };

// clone a new same node 
Node* Node::clone()
{
    return new Node(this->get_info());
};

// Node& Node::operator=(Node& node)
// {
//     this->info = node.get_info();
//     return *this;
// }

// get info about node
c_label Node::get_info() const
{
    return info.c_str();
}

/*-------------*/

// init Edge with basic c_label
Edge::Edge(c_label source, c_label dest) :
    info(""), source(new Node(source)),dest(new Node(dest)) {};

// init Edge with other already allocated node
Edge::Edge(Node* source, Node* dest) :
    info(""), source(source), dest(dest) {};

// Edge::Edge(Edge& e)
// {
//    edge = std::make_pair(e.get_src(), e.get_dst());
// }


// clone a new Edge
Edge* Edge::clone()
{
    return new Edge(source->get_info(), dest->get_info());
}

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
c_label Edge::get_info() 
{
    info = std::string(source->get_info()) + 
        " -> " +
        std::string(dest->get_info());
    return info.c_str();
}

// simplify get_node.get_info method
c_label Edge::get_src_info() const
{
    return source->get_info();
};

// simplify get_node.get_info method
c_label Edge::get_dst_info() const
{
    return dest->get_info();
};

/*-------------*/

Graph::Graph()
{
}

// normally get Graph from here
Graph::Graph(GraphTable table) :
    info("")
{
    // travel table
    for (GraphTable::iterator it = table.begin();
            it != table.end(); it++)
    {
        add_edge(it->first.c_str(), it->second.c_str());
    }
}

Graph::~Graph()
{
    for (GraphBody::iterator it = graph.begin();
            it != graph.end(); it++)
    {
        for (EdgeSet::iterator edge_it = it->second.begin();
                edge_it != it->second.end(); edge_it++)
        {
            delete(*edge_it);
        }
        delete(it->first);
    }
}

// only get edge info, no node info
c_label Graph::get_info()
{
    info = "";
    // travel edge
    for (GraphBody::iterator it = graph.begin();
            it != graph.end(); it++)
    {
        for (EdgeSet::iterator edge_it = it->second.begin();
                edge_it != it->second.end(); edge_it++)
        {
            info += (*edge_it)->get_info() + std::string("\n");
        }
    }
    return info.c_str();
}

size_t Graph::size_node()
{
    return node_cache.size();
}

size_t Graph::size_edge()
{
    size_t accum = 0;
    for (GraphBody::iterator it = graph.begin();
            it != graph.end(); it++)
    {
        accum += (*it).second.size();
    }
    return accum;
}

Node* Graph::find_node(c_label name)
{
    NodeCache::iterator it = node_cache.find(name);
    if ( it == node_cache.end())
        return nullptr;

    return it->second;
}

Edge* Graph::find_edge(c_label source, c_label dest)
{
    NodeCache::iterator node_it = node_cache.find(source);
    // check source existence, since it is a index of edge
    if ( node_it == node_cache.end() )
        return nullptr;

    // get EdgeSet
    GraphBody::iterator graph_it = graph.find( node_it->second );

    // travel EdgeSet
    for ( EdgeSet::iterator edge_it = graph_it->second.begin();
            edge_it != graph_it->second.end();
            edge_it++)
    {
        if ( std::string((*edge_it)->get_dst_info()) == std::string(dest) )
            return *edge_it;
    }

    return nullptr;
}

Node* Graph::add_node(c_label name)
{
    // check node existence
    if ( find_node(name) == nullptr ) 
    {
        // give new node
        Node* temp = new Node(name);
        node_cache.insert( std::make_pair(name, temp) );
        graph.insert( std::make_pair(temp, EdgeSet()));
        return temp;
    }
    return nullptr;
}

Edge* Graph::add_edge(c_label source, c_label dest)
{
    // edge imply two node exist
    // check those two node
    // or add them to graph
    Node* src = find_node(source);
    Node* dst = find_node(dest);

    if (src == nullptr)
        src = add_node(source);

    if (dst == nullptr)
        dst = add_node(dest);

    // check edge existence
    if ( find_edge(source, dest) == nullptr )
    {
        GraphBody::iterator it = graph.find(src);
        it->second.insert( new Edge(src, dst) );
    }

    return nullptr;
}

// not complete
Graph* Graph::breadth_firsh_search(c_label name)
{
    Node* tmp = find_node(name);
    if (tmp == nullptr)
        return nullptr;

    Edge start_point = Edge(tmp, tmp);
    Graph *g = new Graph();

    std::queue<Edge*> que;
    que.push(&start_point);

    while( !que.empty() )
    {
        Node *n_tmp;
        Edge *e_tmp = que.front();
        GraphBody::iterator it;
        c_label new_src_node = e_tmp->get_dst_info();

        if ( g->find_node( new_src_node ) == nullptr)
        {
            if (e_tmp->get_dst_info() != start_point.get_src_info())
                g->add_edge(e_tmp->get_src_info(), e_tmp->get_dst_info());

            que.pop();

            n_tmp = find_node( new_src_node );
            assert(n_tmp != nullptr);
            it = graph.find( n_tmp );

            for (EdgeSet::iterator edge_it = it->second.begin();
                    edge_it != it->second.end(); edge_it++)
            {
                c_label new_dest_node = (*edge_it)->get_dst_info();
                if ( g->find_node( new_dest_node ) == nullptr )
                    que.push( *edge_it );
            }
        }
        else
        {
            que.pop();
        }
    }

    return g;
}

Graph* Graph::depth_firsh_search(c_label name)
{
    Node* tmp = find_node(name);
    if (tmp == nullptr)
        return nullptr;

    Edge start_point = Edge(tmp, tmp);
    Graph *g = new Graph();

    std::stack<Edge*> stk;
    stk.push(&start_point);

    while( !stk.empty() )
    {
        Node *n_tmp;
        Edge *e_tmp = stk.top();
        GraphBody::iterator it;
        c_label new_src_node = e_tmp->get_dst_info();

        if ( g->find_node( new_src_node ) == nullptr)
        {
            if (e_tmp->get_dst_info() != start_point.get_src_info())
                g->add_edge(e_tmp->get_src_info(), e_tmp->get_dst_info());

            stk.pop();

            n_tmp = find_node( new_src_node );
            assert(n_tmp != nullptr);
            it = graph.find( n_tmp );

            for (EdgeSet::iterator edge_it = it->second.begin();
                    edge_it != it->second.end(); edge_it++)
            {
                c_label new_dest_node = (*edge_it)->get_dst_info();
                if ( g->find_node( new_dest_node ) == nullptr )
                    stk.push( *edge_it );
            }
        }
        else
        {
            stk.pop();
        }
    }


    return g;
}


/*--------------------*/

Graph_test::Graph_test():
    gt( { {"1", "2"}, {"1", "3"}, {"2", "4"},
          {"2", "6"}, {"3", "4"}, {"3", "5"},
          {"4", "6"}, {"5", "1"}, {"6", "5"}} ),
    g(gt)
{
    std::cout << g.get_info() << std::endl;

    Graph *bfs = g.breadth_firsh_search("2");
    std::cout << bfs->get_info() << std::endl;
    delete(bfs);
    bfs = g.depth_firsh_search("2");
    std::cout << bfs->get_info() << std::endl;
    delete(bfs);
};
