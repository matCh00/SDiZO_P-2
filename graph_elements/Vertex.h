#pragma once

// klasa reprezentująca wierzchołek
class Vertex {

    int index;       // index (Dijkstra, Prim)
    int key;         // klucz (Prim)
    int distance;    // dystans (Dijkstra)

public:

    Vertex(int, int);    // konstruktor

    int get_vertex_index();     // pobierz indeks
    int get_key();              // pobierz klucz (Prim)
    void set_key(int);          // ustaw klucz (Prim)
    int get_distance();         // pobierz dystans (Dijkstra)
    void set_distance(int);     // ustaw dystans (Dijkstra)
};

