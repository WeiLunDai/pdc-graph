#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <set>
#include <list>
#include <map>

class Node {
private:
    std::string info;

public:
    Node(const char* info);
    //Node(Node& node) ;
    //Node& operator=(Node& node);

    Node *clone();
    virtual const char *get_info() const;
    virtual ~Node() {};
};

class Edge {
private:
    std::pair<Node*, Node*> edge;

public:
    Edge(const char* source, const char* dest);
    Edge(Node& source, Node& dest);
    virtual ~Edge() {};
    //Edge(Edge& e);

    virtual Edge* clone();

    // Node* get_source();
    // Node* get_dest();

    const char* get_source_info();
    const char* get_dest_info();
};

class Graph {
private:
    //typedef std::set<Node*> Nodes;
    typedef std::set<Edge*> Edges;
    typedef std::set<std::string> NodeCache;
    //Nodes nodes;
    Edges edges;
    NodeCache node_cache;

    //bool find_node(Node& n);

public:
    typedef std::map< std::string, std::string > GraphTable;

    Graph(GraphTable table);

    // void add_node(Node& n);
    // void add_edge(Edge& e);
    
    bool find_edge(Edge& e);
    void Dreadth_Firsh_Search();
    void Depth_Firsh_Search();

};

#endif
