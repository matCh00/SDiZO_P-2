#pragma once
#include "../graph_elements/Edge.h"
#include "../graph_elements/Adjacency_List.h"
#include "../graph_elements/Vertex_Min_Heap.h"
using namespace std;

// klasa reprezentująca graf, który jest reprezentowany listą sąsiedztwa

class Graph_List {

    int vertices;    // liczba wierzchołków
    int edges;       // liczba krawędzi

    Adjacency_List **adjacency_list;     // lista sąsiedztwa

public:

    explicit Graph_List(int vertexes = 0);   // konstruktor (explicit - konstruktor nie może być użyty do niejawnych konwersji)
    ~Graph_List();                           // destruktor

    void add_edge(int vertex1, int vertex2, int edge_weight, bool directed);   // dodanie krawędzi

    void Prim_algorithm();           // algorytm Prima
    void Kruskal_algorithm();        // algorytm Kruskala
    void Dijkstra_algorithm();       // algorytm Dijkstry
    void Bellman_Ford_algorithm();   // algorytm Bellmana-Forda

    void print();                                // wypisanie grafu w postaci listy sąsiedztwa
    int kruskal_find_setL(int *parent, int x);   // funkcja pomocnicza do algorytmu Kruskala
};


