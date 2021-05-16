#pragma once
#include "Graph.h"
#include <vector>
using namespace std;


class Graph_Matrix : public Graph {

    vector<vector<int>> incidence_matrix;   // macierz incydencji

public:
    Graph_Matrix(int size, bool directed);
    ~Graph_Matrix();

    void print();
    void add_edge(int origin, int destination, int weight);
    void remove_edge(int origin, int destination);
    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int origin, int destination);
    void ford_bellman_algorithm(int origin, int destination);
};


