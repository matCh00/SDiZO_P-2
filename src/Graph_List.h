#pragma once
#include "Graph.h"
#include <list>
using namespace std;


class Graph_List : public Graph {

    list<int*> adjacency_list;   // lista sąsiedztwa

public:
    Graph_List(int size, bool directed);
    ~Graph_List();

    void print();
    //void add_edge(int origin, int destination, int weight);
    //void remove_edge(int origin, int destination);
    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int origin, int destination);
    void ford_bellman_algorithm(int origin, int destination);
};


