#pragma once
#include <vector>
using namespace std;


class Graph {

private:
    vector<int> vertex_array;                // reprezentuje zbiór wierzchołków

    vector<int> origin_vertex_array;         //
    vector<int> destination_vertex_array;    // reprezentują elementy krawędzi
    vector<int> weight_array;                //

public:
    Graph(int);
    ~Graph();

    void add_edge(int, int, int);
    void add_u_edge(int, int, int);
    void remove_edge(int, int);
    void add_vertex(int);
    void print();
    int find_vertex(int);
    int find_edge(int, int);
};



