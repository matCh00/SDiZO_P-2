#include "Graph.h"
#include <iostream>
using namespace std;


// konstruktor grafu
Graph::Graph(int size, bool directed) {

    // tworzenie wierzchołków numerowanych od 0
    for (int i = 0; i < size; i++){
        add_vertex(i);
    }
};


// destruktor grafu
Graph::~Graph() {

    vertex_array.clear();
    origin_vertex_array.clear();
    destination_vertex_array.clear();
    weight_array.clear();
};


// dodanie wierzchołka
void Graph::add_vertex(int vertex) {

    vertex_array.push_back(vertex);
}


// dodanie krawędzi nieskierowanej
void Graph::add_edge(int origin, int destination, int weight) {

    origin_vertex_array.push_back(origin);
    destination_vertex_array.push_back(destination);
    weight_array.push_back(weight);
}


// dodanie krawędzi skierowanej
void Graph::add_u_edge(int origin, int destination, int weight) {

    add_edge(origin, destination, weight);
    add_edge(destination, origin, weight);
}


// szukanie wierzchołka
int Graph::find_vertex(int vertex) {

    for (int i = 0; i < vertex_array.size(); i++) {
        if (vertex_array[i] == vertex)
            return 1;
    }
    return 0;
}


// szukanie krawędzi
int Graph::find_edge(int origin, int destination) {

    for (int i = 0; i < origin_vertex_array.size(); i++) {
        if (origin_vertex_array[i] == origin && destination_vertex_array[i] == destination)
            return 1;
    }
    return 0;
}


// wypisanie elementów grafu
void Graph::print() {

    cout << "lista wierzcholkow:  ";
    for (int i = 0; i < vertex_array.size(); i++)
        cout << vertex_array[i] << "  ";
    cout << endl << "lista krawedzi: " << endl;
    for (int i = 0; i < origin_vertex_array.size(); i++)
        cout << origin_vertex_array[i] << " -> " << destination_vertex_array[i] << "  (" << weight_array[i] << ")" << endl;
}