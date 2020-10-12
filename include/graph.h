#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <cstring>
#include <memory>
#include <stack>
#include <map>
#include <vector>

typedef const std::string Info;

// requirement:
//  init:
// node(string)     -> init with a string
// node(node&)      -> init with another node
//
//  edit:
// node.add(node)   -> node add a edge
// node.del(node)   -> node delete a edge
//
//  info:
// node.info()      -> provide info about node
// node.isTo(node)  -> has edge to node
// node.edgeSize()  -> out degree of node
//
//  selector:
// node.to()        -> default go to node
// node.next()      -> change default node to next
// node.begin()     -> first node can go to
// node.end()       -> last node can go to

class Node;
class _node {
    friend class Node;
    std::string _info;
    std::vector< std::shared_ptr<Node> > _to;
    size_t _now_at;
};

class Node {
private:
    std::unique_ptr<_node> node;

public:
    // init:
    Node();
    Node(Info name);
    // Node(Node& ref);
    Node(const Node& ref);    
    ~Node();

    const Node& operator=(const Node& rhs) const;
    bool operator==(const Node& rhs) const;
    bool operator!=(Node& rhs);

    // edit:
    void add(Node* dest);
    void del(Node* dest);  

    // info:
    Info info() const; 
    bool isTo(Node* target);
    size_t edgeSize() const;

    // selector:
    void begin();
    Node* to();
    void next();
};

//
// requirement:
//  init:
// edge(node)       -> init with a node
//  
//  info:
// edge.source()    -> source of edge
// edge.dest()      -> dest of edge
// edge.info()      -> info about edge
//
//  selector:
// edge.next()      -> change to next node
// edge.to()        -> node edge can go
// edge.begin()     -> first node edge can go
// edge.end()       -> end node edge can go
//
//  edit:
// edge.move()      -> move source to dest
//

class _edge {
    friend class Edge;
    Node* _source;
    Node* _destination;
    std::string _info;
};

class Edge {
private:
    std::unique_ptr<_edge> edge;

public:
    // init:
    Edge(Node* ref);
    // Edge(Edge& e);
    ~Edge();

    // info:
    const Node& source() const;
    const Node& dest() const;
    Info info();
    bool operator==(Edge& e);
    bool operator!=(Edge& e);

    // selector:
    Node* here();
    Node* to();
    void begin();
    void next();

    // edit:
    void move();     
};

// 
// requirement:
//  init:
// graph(GraphTable)    -> init with a GraphTable
//
//  info:
// graph.find(node)     -> find node return nullptr or address
// graph.find(edge)     -> find edge return nullptr or address
// graph.info()         -> info about graph
// graph.nodeSize()     -> how many nodes in graph
// graph.edgeSize()     -> how many edges in graph
//
//  edit:
// graph.add(node)      -> add new node
// graph.add(edge)      -> add new edge
// graph.del(node)      -> delete node, if exist return true, else return false
// graph.del(edge)      -> delete edge, if exist return true, else return false
//
//  travel:             -> all travel do will not change original graph
// graph.startAt(node)  -> set travel start point, default point is being of graph
// graph.bfs()          -> do bfs 
// graph.dfs()          -> do dfs
//

class _graph {
    friend class Graph;
    std::string _info;
    std::vector< std::shared_ptr<Node> > nodes;
    // std::stack< Node* > stk;
};

class Graph {
private:
    std::unique_ptr<_graph> graph;

public:
    typedef std::multimap< std::string, std::string > GraphTable;
  
    // init:
    Graph();
    Graph(const Graph& ref);
    Graph(GraphTable& gt);
    ~Graph();

    Graph& operator=(const Graph& rhs);

    // info:
    Node* find(Node* target);
    Node* find(Info info);
    Edge* find(Edge* edge);
    Edge* find(Info src_info, Info dest_Info);
    Info info();
    size_t nodeSize();
    size_t edgeSize();

    // selector:
    // void next();

    // edit:
    void add(Node* node);
    void add(Info info);
    void add(Edge* edge);
    void add(Info src_info, Info dest_info);

    bool del(Node* node);
    bool del(Info info);
    bool del(Edge* edge);
    bool del(Info src_info, Info dest_info);

    // travel:
    Graph* breathFirstSearch(Node* node);
    Graph* breathFirstSearch(Info info);
    Graph* depthFirstSearch(Node* node);
    Graph* depthFirstSearch(Info info);

    void exportPng();
};

#endif
