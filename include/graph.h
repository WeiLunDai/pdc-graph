#ifndef __NODE_H__
#define __NODE_H__

#include <cstddef>
#include <string>
#include <set>
#include <map>

typedef const char* c_label;

class Node {
private:
    std::string info;

public:
    Node(c_label info);
    //Node(Node& node) ;
    //Node& operator=(Node& node);

    Node *clone();
    virtual c_label get_info() const;
    virtual ~Node() {};
};

class Edge {
private:
    std::string info;
    // std::pair<Node*, Node*> edge;
    Node *source;
    Node *dest;

public:
    Edge(c_label source, c_label dest);
    Edge(Node* source, Node* dest);
    virtual ~Edge() {};
    //Edge(Edge& e);

    virtual Edge* clone();

    // Node* get_source();
    // Node* get_dest();

    virtual const char *get_info();
    c_label get_src_info() const;
    c_label get_dst_info() const;
};

class Graph {
private:
    //typedef std::set<Node*> Nodes;
    typedef std::set<Edge*> EdgeSet;
    typedef std::map<Node*, EdgeSet > GraphBody;
    typedef std::map<std::string, Node*> NodeCache;
    //Nodes nodes;
    //Edges edges;
    std::string info;
    NodeCache node_cache;
    GraphBody graph;

    //bool find_node(Node& n);

public:
    typedef std::multimap< std::string, std::string > GraphTable;

    Graph();
    Graph(GraphTable table);
    ~Graph();

    // information
    c_label get_info();
    size_t size_node();
    size_t size_edge();

    // TODO: 
    // you should modify or add interface 
    // *responsibility assign:
    //  1. create node and edge by graph itself
    //     so, information is necessary
    //  2. create node and edge by user
    //     graph only handle pointer structure
    //  3. create a handle class for graph 
    //

    Node* find_node(c_label name);
    Edge* find_edge(c_label source, c_label dest);

    Node* add_node(c_label name);
    // bool  add_node(Node* node);
    Edge* add_edge(c_label source, c_label dest);
    // bool  add_edge(Edge* edge);
    // bool del_node(c_label name);
    // bool del_edge(c_label source, c_label dest);

    // void add_node(Node& n);
    // void add_edge(Edge& e);
    
    // bool find_edge(Edge& e);
    Graph* breadth_firsh_search(c_label name);
    Graph* depth_firsh_search(c_label name);

};

// class Graph_test {
//     Graph::GraphTable gt;
//     Graph g;
//     public:
//     Graph_test();
// };

#endif
