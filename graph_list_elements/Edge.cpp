#include "Edge.h"


Edge::Edge(int v1, int v2, int weight) {
    vertex1 = v1;
    vertex2 = v2;
    edge_weight = weight;
}

int Edge::get_vertex1() {
    return vertex1;
}

int Edge::get_vertex2() {
    return vertex2;
}

int Edge::get_edge_weight() {
    return edge_weight;
}

void Edge::set_vertex1(int v1) {
    vertex1 = v1;
}

void Edge::set_vertex2(int v2) {
    vertex2 = v2;
}

void Edge::set_edge_weight(int weight) {
    edge_weight = weight;
}