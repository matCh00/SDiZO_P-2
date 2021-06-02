#include "Vertex_Min_Heap.h"
#include <iostream>

Vertex_Min_Heap::Vertex_Min_Heap(int v) {
    vertexes = new Vertex *[v];
    position = new int[v];

    // stworzenie pomocniczych obiektów - wierzchołków (numer wierzchołka, key)
    for (int i = 0; i < v; ++i) {
        vertexes[i] = new Vertex(i, 999999999);  // po zamianie z INT_MAX nie ma błędów
        position[i] = i;
    }
    heap_size = v;
    original_size = v;
}

Vertex_Min_Heap::~Vertex_Min_Heap() {
    for (int i = 0; i < original_size; ++i) {
        delete vertexes[i];
    }
    delete[] vertexes;
    delete[] position;
}

bool Vertex_Min_Heap::is_in_heap(int v) {
    return position[v] < heap_size;
}

bool Vertex_Min_Heap::has_elements() {
    return heap_size > 0;
}

void Vertex_Min_Heap::create_min_heap() {
    for (int i = (heap_size - 2) / 2; i >= 0; --i)
        min_heapify(i);
}

void Vertex_Min_Heap::min_heapify(int parent_index) {
    int smallest_index = parent_index;
    int left_index = 2 * parent_index + 1;
    int right_index = 2 * parent_index + 2;

    // poszukiwanie najmniejszej wartości
    if ((left_index < heap_size) && vertexes[left_index]->get_element() < vertexes[smallest_index]->get_element())
        smallest_index = left_index;
    if ((right_index < heap_size) && vertexes[right_index]->get_element() < vertexes[smallest_index]->get_element())
        smallest_index = right_index;

    if (smallest_index != parent_index) {
        // zamiana elementów kopca
        position[vertexes[smallest_index]->get_vertex_index()] = parent_index;
        position[vertexes[parent_index]->get_vertex_index()] = smallest_index;
        auto swap = vertexes[parent_index];  // automatyczne ustalenie typu
        vertexes[parent_index] = vertexes[smallest_index];
        vertexes[smallest_index] = swap;
        min_heapify(smallest_index);   // rekurencja
    }
}

Vertex* Vertex_Min_Heap::extract_min() {
    if (heap_size > 0) {
        --heap_size;
        Vertex *min = vertexes[0];
        position[vertexes[0]->get_vertex_index()] = heap_size;
        position[vertexes[heap_size]->get_vertex_index()] = 0;

        auto swap = vertexes[0];  // automatyczne ustalenie typu
        vertexes[0] = vertexes[heap_size];
        vertexes[heap_size] = swap;
        return min;
    }
    return nullptr;
}