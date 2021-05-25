#pragma once
#include "List_Element.h"

// klasa reprezentująca listę sąsiedztwa
// użycie: Graph_List

class Adjacency_List {

    List_Element *head;   // wskaźnik na głowę
    List_Element *tail;   // wskaźnik na ogon
    int list_size;        // długość listy

public:
    Adjacency_List();   // konstruktor
    ~Adjacency_List();  // destruktor

    void add_edge(int neighbour, int weight);    // dodanie krawędzi
    void remove_vertex(List_Element *element);   // usunięcie elementu listy

    List_Element *get_head();   // pobieranie wskaźnika na głowę listy
};


