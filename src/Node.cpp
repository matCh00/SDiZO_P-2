#include "Node.h"

/*
                         weight
        vertex  ------------------------->  next

 */


// inicjalizacja elementu
Node::Node() {
    vertex = 0;       // dany wierzchołek
    weight = 0;       // waga krawędzi
    next = nullptr;   // wierzchołek z którym utworzona jest krawędź
}

// usunięcie elementu
Node::~Node() {
    vertex = 0;
    weight = 0;
    next = nullptr;
}
