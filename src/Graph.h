#pragma once
#include <vector>
using namespace std;


class Graph {

protected:
    vector<int> vertex_array;                // reprezentuje zbiór wierzchołków

    vector<int> origin_vertex_array;         //
    vector<int> destination_vertex_array;    // reprezentują elementy krawędzi
    vector<int> weight_array;                //

public:
    Graph(int size, bool directed);
    ~Graph();

    void add_edge(int origin, int destination, int weight);
    void add_u_edge(int origin, int destination, int weight);
    void remove_edge(int origin, int destination);
    void add_vertex(int vertex);
    void print();
    int find_vertex(int vertex);
    int find_edge(int origin, int destination);
};



