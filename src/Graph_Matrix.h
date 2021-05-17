#pragma once
#include "Vertex.h"
#include <vector>
#include <queue>
using namespace std;

class Graph_Matrix {

    vector<vector<int>> incidence_matrix;   // macierz incydencji

    int vertex_count;
    int edge_count;
    bool directed;

public:
    Graph_Matrix(int vertexes, int edges, bool directed);
    Graph_Matrix(int V);
    ~Graph_Matrix();

    void print();
    void add_edge(int origin, int destination, int weight);
    Graph_Matrix random(int vertexes, float density, bool directed);

    void prim_algorithm();
    void kruskal_algorithm();
    void dijkstra_algorithm(int origin, int destination);
    void dijkstra_algorithm(int origin);
    void ford_bellman_algorithm(int origin, int destination);
};


