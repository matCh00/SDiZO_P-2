#include "Vertex.h"


Vertex::Vertex(int id, int dist) {
    index = id;
    distance = dist;
}

int Vertex::get_vertex_index() {
    return index;
}

int Vertex::get_distance() {
    return distance;
}

void Vertex::set_distance(int dist) {
    distance = dist;
}

int Vertex::get_key() {
    return key;
}

void Vertex::set_key(int k) {
    key = k;
}
