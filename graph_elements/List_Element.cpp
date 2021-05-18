#include "List_Element.h"


List_Element::List_Element(int neighbour, int edge_weight, List_Element *p = nullptr, List_Element *n = nullptr) {

    this->neighbour = neighbour;
    this->edge_weight = edge_weight;
    prev = p;
    next = n;
}
