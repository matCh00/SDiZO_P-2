#include "Graph.h"
#include <iostream>
using namespace std;

int main(){

    Graph *graph = new Graph(6, true);

    graph->add_edge(0, 1, 11);
    graph->add_edge(0, 2, 10);
    graph->add_edge(0, 5, 15);
    graph->add_edge(1, 3, 33);
    graph->add_edge(4, 2, 20);
    graph->add_edge(5, 1, 51);
    graph->add_edge(4, 3, 43);

    graph->print();

    return 0;
}