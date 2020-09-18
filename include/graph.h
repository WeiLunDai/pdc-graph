#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <set>
#include <list>

class Node {
    private:
    std::string info;

    public:
    Node(const char* info);
    Node(Node& node) ;
    Node& operator=(Node& node);

    Node *clone();
    virtual const char *get_info() const;
    virtual ~Node() {};
};

class Edge {
    private:
    std::pair<Node*, Node*> edge;
    public:
    Edge(Node& source,Node& dest);
    Edge(Edge& e);

    Edge* clone();

    Node* get_source();
    Node* get_dest();

    const char* get_source_info();
    const char* get_dest_info();
};

class Graph {
    private:
    typedef std::set<Node*> Nodes;
    typedef std::set<Edge*> Edges;
    Nodes nodes;
    Edges edges;

    bool find_node(Node& n);
    bool find_edge(Edge& e);

    public:
    typedef std::list< std::pair< std::string, std::string > > graph_table;

    void add_node(Node& n);
    void add_edge(Edge& e);

};

#endif
