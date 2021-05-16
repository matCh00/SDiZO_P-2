#pragma once
#include "Graph.h"
#include <vector>
using namespace std;


class Graph_Matrix : public Graph {

    vector<vector<int>> incidence_matrix;

public:
    Graph_Matrix(int, bool);
    ~Graph_Matrix();

    void print();
    void add_edge(int, int, int);
    void remove_edge(int, int);
    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int, int);
    void ford_bellman_algorithm(int, int);
};


