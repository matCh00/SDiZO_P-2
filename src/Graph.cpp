#include "Graph.h"
#include <iostream>
using namespace std;


Graph::Graph() {

    int edge_count = 0;
    int vertex_count = 0;

    vertexes = new int[vertex_count];
    edges = new Edge *[edge_count];

    for (int i = 0; i < edge_count; i++){
        edges[i] = nullptr;
    }
};


Graph::~Graph() {

    int edge_count = 0;
    int vertex_count = 0;
    delete edges;
    delete vertexes;
};


void Graph::add_edge(int origin, int destination, int weight) {

    Edge *edge = new Edge();
    edge->start = origin;
    edge->end = destination;
    edge->weight = weight;

    edges[edge_count] = edge;
    edge_count++;
}


void Graph::print() {

    Edge *edge;

    for(int i = 0; i < edge_count; i++){
        edge = edges[i];

        cout << edge->start << endl;
        cout << edge->end << endl;
        cout << edge->weight <<endl;
        cout << endl;
    }
}