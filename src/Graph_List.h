#pragma once
#include "Min_Heap.h"
#include "Node.h"
using namespace std;


class Graph_List {

    Node **adjacency_list;   // lista sąsiedztwa

    int vertex_count;//
    int edge_count;//
    bool directed;//

public:
    Graph_List(int vertexes, int edges, bool directed);
    ~Graph_List();

    void print();
    void add_edge(int origin, int destination, int weight);
    Graph_List random(int vertexes, float density, bool directed);

    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int origin, int destination);
    void ford_bellman_algorithm(int origin, int destination);
};


