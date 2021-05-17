#pragma once
#include "Min_Heap.h"
using namespace std;

class Graph_Matrix {

    int **incidence_matrix;   // macierz incydencji

    int vertex_count;
    int edge_count;
    bool directed;

    int min_key(int *, bool *);
    int find(int, int *);
    int unify(int, int, int *);

public:
    Graph_Matrix(int vertexes, int edges, bool directed);
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


