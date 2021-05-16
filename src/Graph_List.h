#pragma once
#include "Graph.h"
#include <list>
using namespace std;


class Graph_List : public Graph {

    list<int*> adjacency_list;

public:
    Graph_List(int, bool);
    ~Graph_List();

    void print();
    void add_edge(int, int, int);
    void remove_edge(int, int);
    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int, int);
    void ford_bellman_algorithm(int, int);
};


