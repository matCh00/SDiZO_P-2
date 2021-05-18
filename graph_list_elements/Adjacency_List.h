#pragma once
#include "Vertex.h"

// klasa reprezentująca listę sąsiedztwa
class Adjacency_List {

    Vertex *head;   // wskaźnik na głowę
    Vertex *tail;   // wskaźnik na ogon
    int list_size;  // długość listy

public:
    Adjacency_List();   // konstruktor
    ~Adjacency_List();  // destruktor

    void add_edge(int , int);        // dodanie krawędzi
    bool remove_edge(int);           // usunięcie krawędzi
    void remove_vertex(Vertex *);   // usunięcie wierzchołka

    Vertex *get_head();   // pobieranie wskaźnika na głowę listy

};


