#include "Vertex_Min_Heap.h"
#include <iostream>

Vertex_Min_Heap::Vertex_Min_Heap(int vertices) {
    vertexes = new Vertex *[vertices];
    position = new int[vertices];
    // stworzenie pomocniczych obiektów - wierzchołków (numer wierzchołka, key)
    for (int i = 0; i < vertices; ++i) {
        vertexes[i] = new Vertex(i, INT_MAX / 2);
        position[i] = i;
    }
    heap_size = vertices;
    original_size = vertices;
}

Vertex_Min_Heap::~Vertex_Min_Heap() {
    for (int i = 0; i < original_size; ++i) {
        delete vertexes[i];
    }
    delete[] vertexes;
    delete[] position;
}

bool Vertex_Min_Heap::is_in_heap(int vertex) {
    return position[vertex] < heap_size;
}

bool Vertex_Min_Heap::has_elements() {
    return heap_size > 0;
}

void Vertex_Min_Heap::create_min_heap() {
    for (int i = (heap_size - 2) / 2; i >= 0; --i)
        min_heapify(i);
}

void Vertex_Min_Heap::min_heapify(int parentIndex) {
    int smallestIndex = parentIndex;
    int leftIndex = 2 * parentIndex + 1;
    int rightIndex = 2 * parentIndex + 2;
    if ((leftIndex < heap_size) && vertexes[leftIndex]->get_key() < vertexes[smallestIndex]->get_key())
        smallestIndex = leftIndex;
    if ((rightIndex < heap_size) && vertexes[rightIndex]->get_key() < vertexes[smallestIndex]->get_key())
        smallestIndex = rightIndex;
    if (smallestIndex != parentIndex) {
        // zamiana elementów stosu oraz odnośników do ich pozycji
        position[vertexes[smallestIndex]->get_vertex_index()] = parentIndex;
        position[vertexes[parentIndex]->get_vertex_index()] = smallestIndex;
        auto swap = vertexes[parentIndex];
        vertexes[parentIndex] = vertexes[smallestIndex];
        vertexes[smallestIndex] = swap;
        min_heapify(smallestIndex);
    }
}

Vertex* Vertex_Min_Heap::extract_min() {
    if (heap_size > 0) {
        --heap_size;
        Vertex *mini = vertexes[0];
        position[vertexes[0]->get_vertex_index()] = heap_size;
        position[vertexes[heap_size]->get_vertex_index()] = 0;
        auto swap = vertexes[0];
        vertexes[0] = vertexes[heap_size];
        vertexes[heap_size] = swap;
        return mini;
    }
    return nullptr;
}