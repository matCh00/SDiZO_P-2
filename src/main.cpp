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



    Graph_List *graphL = new Graph_List(6, 6, true);

    graphL->add_edge(0, 4, 1);
    graphL->add_edge(0, 2, 2);
    graphL->add_edge(1, 4, 3);
    graphL->add_edge(2, 3, 4);
    graphL->add_edge(3, 2, 5);
    graphL->add_edge(4, 5, 6);

    graphL->print();


    return 0;
}