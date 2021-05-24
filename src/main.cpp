#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

int main(){

    Graph_Matrix *graphM = new Graph_Matrix(6);

    graphM->add_undirected_edge(0, 4, 3);
    graphM->add_undirected_edge(0, 2, 2);
    graphM->add_undirected_edge(4, 1, 3);
    graphM->add_undirected_edge(2, 3, 1);
    graphM->add_undirected_edge(3, 4, 5);
    graphM->add_undirected_edge(4, 5, 9);

    graphM->print(); //ok

    //graphM->Bellman_Ford_algorithm(); //ok
    //graphM->Kruskal_algorithm(); //ok
    //graphM->Dijkstra_algorithm();  // nie
    graphM->Prim_algorithm();  // nie


cout<<endl<<endl<<endl;


    Graph_List *graphL = new Graph_List(6);

    graphL->add_undirected_edge(0, 4, 3);
    graphL->add_undirected_edge(0, 2, 2);
    graphL->add_undirected_edge(4, 1, 3);
    graphL->add_undirected_edge(2, 3, 1);
    graphL->add_undirected_edge(3, 4, 5);
    graphL->add_undirected_edge(4, 5, 9);

    graphL->print(); //ok

    //graphL->Bellman_Ford_algorithm(); //ok
    //graphL->Kruskal_algorithm(); //ok
    //graphL->Dijkstra_algorithm();  // ok
    graphL->Prim_algorithm();  // nie


    return 0;
}

