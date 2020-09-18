#include "../include/graph.h"
#include <iostream>
#include <utility>

Node::Node(const char* info) : info(info) {};

Node::Node(Node& node) 
{
    this->info = node.get_info();
};

Node* Node::clone()
{
    return new Node(this->get_info());
};

Node& Node::operator=(Node& node)
{
    this->info = node.get_info();
    return *this;
}

const char* Node::get_info() const
{
    return info.c_str();
}

/*-------------*/

Edge::Edge(Node& source,Node& dest) : 
    edge(std::make_pair(source.clone(), dest.clone())) {};

Edge::Edge(Edge& e) 
{
   edge = std::make_pair(e.get_source(), e.get_dest());
}

Edge* Edge::clone() 
{
    return new Edge(*this);
}

Node* Edge::get_source()
{
    return edge.first;
};

Node* Edge::get_dest()
{
    return edge.second;
};

const char* Edge::get_source_info()
{
    return get_source()->get_info();
};

const char* Edge::get_dest_info()
{
    return get_dest()->get_info();
};

/*-------------*/

bool Graph::find_node(Node& n) {
    bool isHas = false;
    for (Nodes::iterator it = nodes.begin(); it != nodes.end(); it++) 
    {
        if ( (*it)->get_info() == n.get_info() )
        {
            isHas = true;
            break;
        }
    }
    return isHas;
}

bool Graph::find_edge(Edge& e) {
    bool isHas = true;
    for (Edges::iterator it = edges.begin(); it != edges.end(); it++)
    {
        if ( (*it)->get_source_info() == e.get_source_info() &&
                (*it)->get_dest_info() == e.get_dest_info())
        {
            isHas = false;
            break;
        }
    }
    return isHas;
}

void Graph::add_node(Node& n) 
{
    if (!find_node(n))
        nodes.insert(n.clone());
}

void Graph::add_edge(Edge& e)
{
    if (!find_edge(e))
        edges.insert(e.clone());
}
