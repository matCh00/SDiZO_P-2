#include "Vertex.h"
#include <iostream>


Vertex::Vertex(int index)
{
    this->index = index;
    this->cost = 0;
    this->connected_matrix = -1;
}

Vertex::Vertex()
{
    this->index = -1;
    this->cost = INT_MAX;
    this->connected_matrix = -1;
}

Vertex::~Vertex()
{
}

