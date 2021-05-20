#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

int main(){

    Graph_Matrix *graphM = new Graph_Matrix(6);

    graphM->add_directed_edge(0, 4, 3);
    graphM->add_directed_edge(0, 2, 2);
    graphM->add_directed_edge(4, 1, 3);
    graphM->add_directed_edge(2, 3, 1);
    graphM->add_directed_edge(3, 4, 5);
    graphM->add_directed_edge(4, 5, 9);

    graphM->print();

    graphM->Bellman_Ford_algorithm(0);

cout<<endl<<endl<<endl;

    Graph_List *graphL = new Graph_List(6);

    graphL->add_directed_edge(0, 4, 3);
    graphL->add_directed_edge(0, 2, 2);
    graphL->add_directed_edge(4, 1, 3);
    graphL->add_directed_edge(2, 3, 1);
    graphL->add_directed_edge(3, 4, 5);
    graphL->add_directed_edge(4, 5, 9);

    graphL->print();

    graphL->Bellman_Ford_algorithm(0);

    return 0;
}

