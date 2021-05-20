#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

int main(){

    Graph_Matrix *graphM = new Graph_Matrix(6);

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
cout<<endl<<endl<<endl;

    Graph_List *graphL = new Graph_List(6);

    graphL->add_undirected_edge(0, 4, 3);
    graphL->add_undirected_edge(0, 2, 2);
    graphL->add_undirected_edge(1, 4, 3);
    graphL->add_undirected_edge(2, 3, 1);
    graphL->add_undirected_edge(3, 2, 5);
    graphL->add_undirected_edge(4, 5, 9);

    graphL->print();
    int *keyL = new int[6];
    int *parentL = new int[6];

    graphL->Prim_algorithm(keyL, parentL, 0);

    cout << "Algorytm Prima listowo; wierzcholek: key/parent\n";
    for (int i = 0; i < 6; ++i) {
        cout << i << ": " << keyL[i] << "/" << parentL[i] << "\n";
    }
    cout << "\nKrawedzie MST:\n";
    for (int i = 0; i < 6; ++i) {
        if (parentL[i] != -1) {
            cout << i << " - " << parentL[i] << " : Waga = " << keyL[i] << "\n";
        }
    }


    return 0;
}

