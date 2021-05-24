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

    graphM->print(); //ok

    // directed
    //graphM->Bellman_Ford_algorithm(); //ok
    //graphM->Dijkstra_algorithm();  // ok

    // undirected
    //graphM->Prim_algorithm();  // ok
    //graphM->Kruskal_algorithm(); //ok


cout<<endl<<endl<<endl;


    Graph_List *graphL = new Graph_List(6);

    graphL->add_directed_edge(0, 4, 3);
    graphL->add_directed_edge(0, 2, 2);
    graphL->add_directed_edge(4, 1, 3);
    graphL->add_directed_edge(2, 3, 1);
    graphL->add_directed_edge(3, 4, 5);
    graphL->add_directed_edge(4, 5, 9);

    graphL->print(); //ok

    // directed
    //graphL->Bellman_Ford_algorithm(); //ok
    //graphL->Dijkstra_algorithm();  // ok

    // undirected
    //graphL->Kruskal_algorithm(); //ok
    //graphL->Prim_algorithm();  // ok


    return 0;
}

