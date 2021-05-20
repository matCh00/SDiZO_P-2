#pragma once
#include "C:\Users\matic\OneDrive\Pulpit\SDiZO_P-2-v2\graph_elements\Edge.h"
#include "C:\Users\matic\OneDrive\Pulpit\SDiZO_P-2-v2\graph_elements\Adjacency_List.h"
#include "C:\Users\matic\OneDrive\Pulpit\SDiZO_P-2-v2\graph_elements\Vertex_Min_Heap.h"
using namespace std;

// klasa reprezentująca graf, który jest reprezentowany listą sąsiedztwa
class Graph_List {

    int vertices;    // liczba wierzchołków
    int edges;       // liczba krawędzi

    Adjacency_List **adjacency_list;     // lista sąsiedztwa

public:

    explicit Graph_List(int vertices = 0);   // konstruktor
    ~Graph_List();                           // destruktor

    void add_vertex();                         // dodaj wierzchołek
    void add_undirected_edge(int, int, int);   // dodaj krawęź nieskierowaną
    void add_directed_edge(int, int, int);     // dodaj krawęź skierowaną

    void Prim_algorithm(int *&, int *&, int);           // algorytm Prima
    void Kruskal_algorithm(Edge **);                    // algorytm Kruskala
    void Dijkstra_algorithm(int *&, int *&, int);       // algorytm Dijkstry
    void Bellman_Ford_algorithm(int);   // algorytm Bellmana-Forda

    void print();        // wypisz graf w postaci listy sąsiedztwa
    int get_vertices();  // pobierz liczbę wierzchołków
    int get_edges();     // pobierz liczbę krawędzi
};


