#pragma once
#include "List_Element.h"

// klasa reprezentująca listę sąsiedztwa
class Adjacency_List {

    List_Element *head;   // wskaźnik na głowę
    List_Element *tail;   // wskaźnik na ogon
    int list_size;  // długość listy

public:
    Adjacency_List();   // konstruktor
    ~Adjacency_List();  // destruktor

    void add_edge(int , int);        // dodanie krawędzi
    bool remove_edge(int);           // usunięcie krawędzi
    void remove_vertex(List_Element *);   // usunięcie wierzchołka

    List_Element *get_head();   // pobieranie wskaźnika na głowę listy

};


