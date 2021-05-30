#pragma once
#include <iostream>
#include "../graph_elements/Edge.h"
#include "../graph_elements/Incidence_Matrix.h"
#include "../graph_elements/Vertex_Min_Heap.h"
using namespace std;

// klasa reprezentująca graf, który jest reprezentowany jako macierz incydencji

class Graph_Matrix {

    int vertices;        // liczba wierzchołków
    int edges;           // liczba krawędzi
    int *edge_weights;   // wagi krawędzi

    Incidence_Matrix *incidence_matrix;   // macierz incydencji

public:

    explicit Graph_Matrix(int vertexes = 0);   // konstruktor (explicit - konstruktor nie może być użyty do niejawnych konwersji)
    ~Graph_Matrix();                           // destruktor

    void add_edge(int vertex1, int vertex2, int weight, bool directed);   // dodanie krawędzi
    void new_edge_weights(int added_weight);                              // dodanie wagi krawędzi

    void Prim_algorithm(int *&key, int *&parent);                // algorytm Prima
    void Kruskal_algorithm(Edge **mst_edges);                    // algorytm Kruskala
    void Dijkstra_algorithm(int *&distance, int *&parent);       // algorytm Dijkstry
    bool Bellman_Ford_algorithm(int *&distance, int *&parent);   // algorytm Bellmana-Forda

    void Dijkstra();      // algorytm wraz z wypisaniem
    void Bellman_Ford();  // algorytm wraz z wypisaniem
    void Prim();          // algorytm wraz z wypisaniem
    void Kruskal();       // algorytm wraz z wypisaniem

    void print();                                     // wypisanie grafu w postaci listy sąsiedztwa
    int kruskal_find_setM(int *parent, int x);        // funkcja pomocnicza do algorytmu Kruskala
};


