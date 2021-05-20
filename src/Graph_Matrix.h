#pragma once
#include <iostream>
#include "C:\Users\matic\OneDrive\Pulpit\SDiZO_P-2-v2\graph_elements\Edge.h"
#include "C:\Users\matic\OneDrive\Pulpit\SDiZO_P-2-v2\graph_elements\Incidence_Matrix.h"
#include "../graph_elements/Vertex_Min_Heap.h"
using namespace std;

class Graph_Matrix {

    int vertices;        // liczba wierzchołków
    int edges;           // liczba krawędzi
    int *edge_weights;   // wagi krawędzi

    Incidence_Matrix *incidence_matrix;   // macierz incydencji

public:

    explicit Graph_Matrix(int vertices = 0);   // konstruktor
    ~Graph_Matrix();                           // destruktor

    void add_undirected_edge(int vertex1, int vertex2, int weight);   // dodaj krawędź nieskierowaną
    void add_directed_edge(int vertex1, int vertex2, int weight);     // dodaj krawędź skierowaną
    void new_edge_weights(int added_weight);                          // wagi

    void Prim_algorithm(int *&key, int *&parent, int start_vertex = 0);                // algorytm Prima
    void Kruskal_algorithm(Edge **mst_edges);                                          // algorytm Kruskala
    void Dijkstra_algorithm(int *&distance, int *&parent, int start_vertex = 0);       // algorytm Dijkstry
    bool Bellman_Ford_algorithm(int *&distance, int *&parent, int start_vertex = 0);   // algorytm Bellmana-Forda

    void print();        // wypisz graf w postaci listy sąsiedztwa
    int get_vertices();  // pobierz liczbę wierzchołków
    int get_edges();     // pobierz liczbę krawędzi
};


