#pragma once
#include "Vertex.h"

// klasa reprezentująca kopiec minimalny wierzchołków
class Vertex_Min_Heap {

    int heap_size;
    int original_size;

public:

    Vertex **vertexes;
    int *position;        // position[i] - zwrócenie pozycji wierzchołka i

    Vertex_Min_Heap(int);   // konstruktor
    ~Vertex_Min_Heap();     // destruktor

    bool is_in_heap(int);    // czy jest w kopcu
    bool has_elements();     // czy ma elementy
    void create_mni_heap();  // tworzenie kopca minimalnego
    void min_heapify(int);   // naprawa w dół kopca minimalnego

    Vertex *extract_min();   // pobranie najmniejszego elementu i usunięcie go z kopca
};



