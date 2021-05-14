#pragma once
#include "list.h"


class Graph_List {

    int edge;
    int vertex;
    int density;
    List *directed_graph;
    List *not_directed_graph;

public:
    Graph_List();
    ~Graph_List();

    void create_random();
    void load();
    void clear();
    void print();

    void dijkstra(int, int);
    void ford_bellman(int, int);
    void prim();
    void kruskal();
};



