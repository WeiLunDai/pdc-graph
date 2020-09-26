#ifndef __NODE_H__
#define __NODE_H__

#include <cstddef>
#include <string>
#include <stack>
#include <queue>
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
    std::vector<Node*> _to;
    size_t _now_at;
    //std::vector<Node*>::iterator _now_at;
};

class Node {
private:
    _node* node;
//     std::string info;
//     std::list<Node*> to;
//     std::list<Node*>::iterator now_at;
    

public:
    // init:
    Node();
    Node(Info name);
    // Node(Node& ref);
    Node(const Node& ref);    
    ~Node();
    const Node& operator=(const Node& rhs) const;
    // bool operator==(Node& rhs);
    bool operator==(const Node& rhs) const;
    bool operator!=(Node& rhs);

    // edit:
    void add(Node& dest);
    void del(Node& dest);  

    // info:
    Info info() const; 
    bool isTo(Node& node);
    size_t edgeSize() const;

    // selector:
    void begin();
    Node& to();
    void next();
    // typedef std::list<Node*>::iterator to_ref;
    // Node(Info info);
    // //Node(Node& node) ;
    // //Node& operator=(Node& node);
    //
    // Node* clone();
    // void add();
    // virtual Info get_info() const;
    // virtual ~Node() {};
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
    _edge* edge;
    // std::string info;
    // // std::pair<Node*, Node*> edge;
    // Node *source;
    // Node *dest;

public:
    // init:
    Edge(Node& ref);
    // Edge(Edge& e);
    ~Edge();

    // info:
    const Node& source() const;
    const Node& dest() const;
    Info info();
    bool operator==(Edge& e);
    bool operator!=(Edge& e);

    // selector:
    Node& here();
    Node& to();
    void begin();
    void next();

    // edit:
    void move();     
    // Edge(Info source, Info dest);
    // Edge(Node* source, Node* dest);
    // virtual ~Edge() {};
    // //Edge(Edge& e);
    //
    // virtual Edge* clone();
    //
    // // Node* get_source();
    // // Node* get_dest();
    //
    // virtual const char *get_info();
    // Info get_src_info() const;
    // Info get_dst_info() const;
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
//
class Graph;
class _graph {
    friend class Graph;
    std::string _info;
    std::vector<Node*> nodes;
    std::stack<Node*> stk;
    // std::queue<Node*> que;
    Edge* edge;
    Graph* travel_graph;
};

class Graph {
private:
    _graph* graph;
    //typedef std::set<Node*> Nodes;
    // typedef std::set<Edge*> EdgeSet;
    // typedef std::map<Node*, EdgeSet > GraphBody;
    // typedef std::map<std::string, Node*> NodeCache;
    // //Nodes nodes;
    // //Edges edges;
    // std::string info;
    // NodeCache node_cache;
    // GraphBody graph;
    // Edge edge;
    //bool find_node(Node& n);
    // Node* find_sub(Node& source, Node& target);

public:
    typedef std::multimap< std::string, std::string > GraphTable;
  
    // init:
    Graph();
    Graph(GraphTable);
    ~Graph();

    // info:
    Node* find(Node& target);
    Edge* find(Edge& edge);
    Info info();
    size_t nodeSize();
    size_t edgeSize();

    // selector:
    // Node& nowAt();
    // Node& to();
    void next();

    // edit:
    bool add(Node& node);
    bool add(Edge& edge);
    bool del(Node& node);
    bool del(Edge& edge);

    // travel:
    // bool startAt(Node& node);
    bool breathFirstSearch(Node& node);
    bool depthFirstSearch(Node& node);
    // Graph();
    // Graph(GraphTable table);
    // ~Graph();
    //
    // // information
    // Info get_info();
    // size_t size_node();
    // size_t size_edge();
    //
    // // TODO:
    // // you should modify or add interface
    // // *responsibility assign:
    // //  1. create node and edge by graph itself
    // //     so, information is necessary
    // //  2. create node and edge by user
    // //     graph only handle pointer structure
    // //  3. create a handle class for graph
    // //
    //
    // Node* find_node(Info name);
    // Edge* find_edge(Info source, Info dest);
    //
    // Node* add_node(Info name);
    // // bool  add_node(Node* node);
    // Edge* add_edge(Info source, Info dest);
    // // bool  add_edge(Edge* edge);
    // // bool del_node(Info name);
    // // bool del_edge(Info source, Info dest);
    //
    // // void add_node(Node& n);
    // // void add_edge(Edge& e);
    //
    // // bool find_edge(Edge& e);
    // Graph* breadth_firsh_search(Info name);
    // Graph* depth_firsh_search(Info name);
    //
};

// class Graph_test {
//     Graph::GraphTable gt;
//     Graph g;
//     public:
//     Graph_test();
// };

#endif
