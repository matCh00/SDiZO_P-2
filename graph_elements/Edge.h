#pragma once

// klasa reprezentująca krawędź
// użycie: Graph_List, Graph_Matrix

class Edge {

    int vertex1;       // wierzchołek początkowy
    int vertex2;       // wierzchołek końcowy
    int edge_weight;   // waga krawędzi

public:

    Edge(int v1, int v2, int weight);  // konstruktor

    int get_vertex1();       // pobranie wierzchołka początkowego
    int get_vertex2();       // pobranie wierzchołka końcowego
    int get_edge_weight();   // pobranie wagi krawędzi

    void set_vertex1(int v1);           // ustawianie wierzchołka początkowego
    void set_vertex2(int v2);           // ustawianie wierzchołka końcowego
    void set_edge_weight(int weight);   // ustawianie wagi krawędzi
};



