#pragma once

// klasa reprezentująca element listy sąsiedztwa
// użycie: Adjacency_List

class List_Element {

public:
    int neighbour;      // sąsiad
    int edge_weight;    // waga krawędzi

    List_Element *next;     // wskaźnik na następny element
    List_Element *prev;     // wskaźnik na poprzedni element

    explicit List_Element(int, int, List_Element *, List_Element *);  // konstruktor - nie może być używany
                                                                      // jako niejawne operatory przekształcenia
};


