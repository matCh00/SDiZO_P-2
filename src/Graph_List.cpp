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


Graph_List::Graph_List(int vertices) {
    this->vertices = vertices;
    edges = 0;
    adjacency_list = new Adjacency_List *[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjacency_list[i] = new Adjacency_List();
    }
}

Graph_List::~Graph_List() {
    for (int i = 0; i < vertices; ++i)
        delete adjacency_list[i];
    delete[] adjacency_list;
}

void Graph_List::add_vertex() {
    auto newAdjacencyLists = new Adjacency_List *[vertices + 1];
    for (int i = 0; i < vertices; ++i) {
        newAdjacencyLists[i] = adjacency_list[i];
        delete adjacency_list[i];
    }
    newAdjacencyLists[vertices] = new Adjacency_List();
    delete[] adjacency_list;
    ++vertices;
}

void Graph_List::add_undirected_edge(int vertex1, int vertex2, int edgeWeight) {
    adjacency_list[vertex1]->add_edge(vertex2, edgeWeight);
    adjacency_list[vertex2]->add_edge(vertex1, edgeWeight);
    ++edges;
}

void Graph_List::add_directed_edge(int vertex1, int vertex2, int edgeWeight) {
    adjacency_list[vertex1]->add_edge(vertex2, edgeWeight);
    ++edges;
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

