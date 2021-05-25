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

    void add_undirected_edge(int vertex1, int vertex2, int weight);   // dodanie krawędzi nieskierowanej
    void add_directed_edge(int vertex1, int vertex2, int weight);     // dodanie krawędzi skierowanej
    void new_edge_weights(int added_weight);                          // dodanie wagi krawędzi

    void Prim_algorithm();           // algorytm Prima
    void Kruskal_algorithm();        // algorytm Kruskala
    void Dijkstra_algorithm();       // algorytm Dijkstry
    void Bellman_Ford_algorithm();   // algorytm Bellmana-Forda

    void print();                                  // wypisanie grafu w postaci listy sąsiedztwa
    int kruskal_find_setM(int *parent, int x);     // funkcja pomocnicza do algorytmu Kruskala
};


