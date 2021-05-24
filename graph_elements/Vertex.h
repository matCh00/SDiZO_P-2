#pragma once

// klasa reprezentująca wierzchołek - potrzebne do kopca minimalnego
// w algorytmie Dijkstry oraz Prima
// użycie: Vertex_Min_Heap

class Vertex {

    int index;      // index (Dijkstra, Prim)
    int element;    // dystans (Dijkstra), klucz (Prim)

public:

    Vertex(int, int);    // konstruktor

    int get_vertex_index();     // pobierz indeks
    int get_element();          // pobierz dystans (Dijkstra), pobierz klucz (Prim)
    void set_element(int);      // ustaw dystans (Dijkstra), ustaw klucz (Prim)
};

