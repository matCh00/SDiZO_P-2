#pragma once


class Graph_Matrix {

    int edge;
    int vertex;
    int density;

    int **directed_graph;
    int **not_directed_graph;
    int ** wages;

public:
    Graph_Matrix();
    ~Graph_Matrix();

    void create_random();
    void load();
    void clear();
    void print();

    void dijkstra(int, int);
    void ford_bellman(int, int);
    void prim();
    void kruskal();
};



