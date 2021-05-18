#pragma once

// klasa reprezentująca wierzchołek
class Vertex {

public:
    int neighbour;      //wartość elementu
    int edge_weight;

    Vertex *next;     // wskaźnik na następny element
    Vertex *prev;     // wskaźnik na poprzedni element

    explicit Vertex(int, int, Vertex *, Vertex *);
};


