#pragma once
#include "../graph_elements/Edge.h"
#include "../graph_elements/Adjacency_List.h"
#include "../graph_elements/Vertex_Min_Heap.h"
using namespace std;

// klasa reprezentująca graf, który jest reprezentowany listą sąsiedztwa

class Graph_List {

    int vertices;    // liczba wierzchołków
    int edges;        // liczba krawędzi

    Adjacency_List **adjacency_list;     // lista sąsiedztwa

public:

    explicit Graph_List(int vertexes = 0);   // konstruktor (explicit - konstruktor nie może być użyty do niejawnych konwersji)
    ~Graph_List();                           // destruktor

    void add_edge(int vertex1, int vertex2, int edge_weight, bool directed);   // dodanie krawędzi

    void Prim_algorithm(int *&key, int *&parent);                                     // algorytm Prima
    void Kruskal_algorithm(Edge **mst_edges);                                         // algorytm Kruskala
    void Dijkstra_algorithm(int *&distance, int *&parent, int starting_vertex);       // algorytm Dijkstry
    bool Bellman_Ford_algorithm(int *&distance, int *&parent, int starting_vertex);   // algorytm Bellmana-Forda

    void Dijkstra();      // algorytm wraz z wypisaniem
    void Bellman_Ford();  // algorytm wraz z wypisaniem
    void Prim();          // algorytm wraz z wypisaniem
    void Kruskal();       // algorytm wraz z wypisaniem

    void print();                                     // wypisanie grafu w postaci listy sąsiedztwa
    int kruskal_find_setL(int *parent, int x);        // funkcja pomocnicza do algorytmu Kruskala
};


