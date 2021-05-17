#pragma once


class Edge {

    int vertex1;       // wierzchołek początkowy
    int vertex2;       // wierzchołek końcowy
    int edge_weight;   // waga krawędzi

public:

    Edge(int, int, int);  // konstruktor

    int get_vertex1();       // pobranie wierzchołka początkowego
    int get_vertex2();       // pobranie wierzchołka końcowego
    int get_edge_weight();   // pobranie wagi krawędzi

    void set_vertex1(int);       // ustawianie wierzchołka początkowego
    void set_vertex2(int);       // ustawianie wierzchołka końcowego
    void set_edge_weight(int);   // ustawianie wagi krawędzi
};



