#include "Graph.h"
#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

int main(){

    Graph_Matrix *graphM = new Graph_Matrix(6, 6, true);

    graphM->add_edge(0, 4, 1);
    graphM->add_edge(0, 2, 2);
    graphM->add_edge(1, 4, 3);
    graphM->add_edge(2, 3, 4);
    graphM->add_edge(3, 2, 5);
    graphM->add_edge(4, 5, 6);

    graphM->print();


    return 0;
}