#pragma once
#include "Edge.h"


class Graph {

public:
    int edge_count;
    int vertex_count;

    Edge **edges;
    int *vertexes;

    Graph();
    ~Graph();

    void add_edge(int, int, int);
    void print();
};



