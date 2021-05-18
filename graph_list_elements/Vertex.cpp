#include "Vertex.h"


Vertex::Vertex(int neighbour, int edge_weight, Vertex *p = nullptr, Vertex *n = nullptr) {

    this->neighbour = neighbour;
    this->edge_weight = edge_weight;
    prev = p;
    next = n;
}
