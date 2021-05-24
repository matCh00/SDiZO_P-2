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

    explicit Graph_List(int vertices = 0);   // konstruktor
    ~Graph_List();                           // destruktor

    void add_vertex();                         // dodanie wierzchołka
    void add_undirected_edge(int, int, int);   // dodanie krawędzi nieskierowanej
    void add_directed_edge(int, int, int);     // dodanie krawędzi skierowanej

    void Prim_algorithm();           // algorytm Prima
    void Kruskal_algorithm();        // algorytm Kruskala
    void Dijkstra_algorithm();       // algorytm Dijkstry
    void Bellman_Ford_algorithm();   // algorytm Bellmana-Forda

    void print();        // wypisanie grafu w postaci listy sąsiedztwa
    int get_vertices();  // pobranie liczby wierzchołków
    int get_edges();     // pobranie liczby krawędzi
    int kruskal_find_setL(int *, int);   // funkcja pomocnicza do algorytmu Kruskala
};


