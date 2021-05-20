#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

int main(){

    /*Graph_Matrix *graphM = new Graph_Matrix(6);

    graphM->add_undirected_edge(0, 4, 3);
    graphM->add_undirected_edge(0, 2, 2);
    graphM->add_undirected_edge(1, 4, 3);
    graphM->add_undirected_edge(2, 3, 1);
    graphM->add_undirected_edge(3, 2, 5);
    graphM->add_undirected_edge(4, 5, 9);

    graphM->print();
    int *key = new int[6];
    int *parent = new int[6];

    graphM->Prim_algorithm(key, parent, 0);

    cout << "Algorytm Prima listowo; wierzcholek: key/parent\n";
    for (int i = 0; i < 6; ++i) {
        cout << i << ": " << key[i] << "/" << parent[i] << "\n";
    }
    cout << "\nKrawedzie MST:\n";
    for (int i = 0; i < 6; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : Waga = " << key[i] << "\n";
        }
    }
cout<<endl<<endl<<endl;*/

    Graph_List *graph = new Graph_List(6);

    graph->add_directed_edge(0, 4, 3);
    graph->add_directed_edge(0, 2, 2);
    graph->add_directed_edge(4, 1, 3);
    graph->add_directed_edge(2, 3, 1);
    graph->add_directed_edge(3, 4, 5);
    graph->add_directed_edge(4, 5, 9);

    graph->print();


    graph->Bellman_Ford_algorithm(0);

    return 0;
}

