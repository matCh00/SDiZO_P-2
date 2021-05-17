#include "Graph_List.h"
#include <iostream>
#include <iomanip>
using namespace std;


/*-----------------------------LISTA SĄSIEDZTWA-----------------------------

        ----------
       |          |           ------                  ------
       |   V1  <--|------->  |  V4  |  <---------->  |  V3  |  <---------->   ...
       |          |           ------                  ------
       |          |
       |          |           ------                  ------
       |   V2  <--|------->  |  V5  |  <---------->  |  V8  |  <---------->   ...
       |          |           ------                  ------
       |          |
       |          |           ------                  ------
       |   V3  <--|------->  |  V6  |  <---------->  |  V1  |  <---------->   ...
       |          |           ------                  ------
       |          |
        ----------

            ^
            |
   to jest tablica wskaźników na tablice


*/


// tworzenie (pustego) grafu - reprezentacja listowa (dzidziczenie po obiekcie Graph)
Graph_List::Graph_List(int vertexes, int edges, bool directed) {

    vertex_count = vertexes;
    edge_count = 0;
    this->directed = directed;

    // każdy element ma wartość NULL
    for (int i = 0; i < vertex_count; i++)
        adjacency_list.push_back(nullptr);
}


// usuwanie grafu
Graph_List::~Graph_List() {

    // usuwanie wszystkich elementów
    for (int i = 0; i < vertex_count; i++)
        adjacency_list.pop_back();
}


// wypisanie grafu w postaci macierzy
void Graph_List::print() {

    Node *node;

    cout << "\nGraf - lista:" << endl << endl;

    for (int v = 0; v < vertex_count; v++) {

        cout << "[" << v << "] ";
        node = adjacency_list[v];

        while (node) {
            cout << "  -> " << setw(3) << "(" << node->vertex << ")";   // wypisanie wszystkich krawędzi wychodzących z tego wierzchołka
            node = node->next;
        }
        cout << endl;
    }
}


// dodanie krawędzi
void Graph_List::add_edge(int origin, int destination, int weight) {

    Node *node = new Node();            // nowe połączenie
    node->vertex = destination;         // wierzchołek początkowy
    node->weight = weight;              // przypisanie wagi
    node->next = adjacency_list[origin];   // wierzchołek końcowy krawędzi
    adjacency_list[origin] = node;         // dodanie nowej krawędzi

    // jeżeli graf nie jest skierowany
    if (!directed) {
        node = new Node();              // nowe połączenie
        node->vertex = origin;          // wierzchołek początkowy
        node->weight = weight;          // przypisanie wagi
        node->next = adjacency_list[destination];   // wierzchołek końcowy krawędzi
        adjacency_list[destination] = node;         // dodanie nowej krawędzi
    }

    edge_count++;
}


// losowe generowanie grafu
Graph_List Graph_List::random(int vertexes, float density, bool directed){

    int ed;

    if (directed)
        ed = vertexes * (vertexes - 1);
    else
        ed = (vertexes * (vertexes - 1)) / 2;


    int edg = (int)(density * ed / 100);

    Graph_List *graph = new Graph_List(vertexes, edg, directed);

    //TODO add edges

    return *graph;
}




//=============================================================================================
//                                     ALGORYTM  DIJKSTRY
//=============================================================================================

// algorytm Dijkstry służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków






//=============================================================================================
//                               ALGORYTM  FORDA-BELLMANA
//=============================================================================================

// algorytm Forda-Bellmana służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków
// w porównaniu do Dijkstry opiera się na metodzie relaksacji
// nie opiera się na założeniu że wagi w grafie są nieujemne






//=============================================================================================
//                                     ALGORYTM  PRIMA
//=============================================================================================

// MST - minimalne drzewo rozpinające (graf nieskierowany)
// MST zawiera wszystkie wierzchołki grafu i podzbiór jego krawędzi
// MST grafu to jego podgraf z którego usunięto niektóre krawędzie (aby nie było cykli)






//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================


