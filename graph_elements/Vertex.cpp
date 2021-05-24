#include "Vertex.h"


Vertex::Vertex(int id, int elem) {
    index = id;
    element = elem;
}

int Vertex::get_vertex_index() {
    return index;
}

int Vertex::get_element() {
    return element;
}

void Vertex::set_element(int elem) {
    element = elem;
}


