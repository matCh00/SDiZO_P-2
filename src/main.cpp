#include "Graph.h"
#include <iostream>
using namespace std;

int main(){

    Graph *graph = new Graph();

    graph->add_edge(0, 1, 2);
    graph->add_edge(0, 2, 3);
    graph->add_edge(0, 3, 4);

    graph->print();

    return 0;
}