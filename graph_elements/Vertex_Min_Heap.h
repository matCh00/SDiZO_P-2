#pragma once
#include "Vertex.h"

// klasa reprezentująca kopiec minimalny wierzchołków - lista priorytetowa
// w algorytmie Dijkstry oraz Prima
// użycie: Graph_List, Graph_Matrix

class Vertex_Min_Heap {

    int heap_size;      // wielkość kopca
    int original_size;  // początkowa wielkość kopca

public:

    Vertex **vertexes;    // zbiór wierzchołków w kopcu
    int *position;        // pozycja wierzchołka

    Vertex_Min_Heap(int v);   // konstruktor
    ~Vertex_Min_Heap();       // destruktor

    bool is_in_heap(int v);    // czy jest w kopcu
    bool has_elements();       // czy ma elementy
    void create_min_heap();    // tworzenie kopca minimalnego
    void min_heapify(int parent_index);   // naprawa w dół kopca minimalnego

    Vertex *extract_min();   // pobranie najmniejszego elementu i usunięcie go z kopca
};



