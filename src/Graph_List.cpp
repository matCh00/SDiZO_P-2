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

void Graph_List::print() {
    for (int i = 0; i < vertices; ++i) {
        cout << "Wierz. " << i << " Nastepnicy: ";
        auto listTraverse = adjacency_list[i]->get_head();
        while (listTraverse != nullptr) {
            cout << listTraverse->neighbour << " waga: " << listTraverse->edge_weight << ";\t";
            listTraverse = listTraverse->next;
        }
        cout << "\n";
    }
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

void Graph_List::Bellman_Ford_algorithm(int startingVertex = 0) {
    Edge **graphEdges = new Edge *[edges];
    int *distance = new int[vertices];
    int *parent = new int[vertices];

    int i = 0;
    for (int j = 0; j < vertices; ++j) {
        distance[j] = INT_MAX / 2;
        parent[j] = -1;
        auto listTraverse = adjacency_list[j]->get_head();
        while (listTraverse != nullptr) {
            graphEdges[i] = new Edge(j, listTraverse->neighbour, listTraverse->edge_weight);
            ++i;
            listTraverse = listTraverse->next;
        }
    }
    parent[startingVertex] = startingVertex;
    distance[startingVertex] = 0;
    bool relaxed = true;
    for (int ii = 1; ii < vertices && relaxed; ++ii) {
        relaxed = false;
        for (int j = 0; j < edges; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->get_vertex1();
            int v = edge->get_vertex2();
            int weight = edge->get_edge_weight();
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                relaxed = true;
            }
        }
    }

    if (relaxed) {
        cout << "Wykryto cykl o lacznej ujemnej wadze\n";
    } else {
        cout << "Algorytm Bellmana-Forda listowo; Wierzcholek: distance/parent\n";
        for (int i = 0; i < vertices; ++i) {
            cout << i << ": " << distance[i] << "/" << parent[i] << "\n";
        }
    }

    if (relaxed) {
        for (int j = 0; j < edges; ++j) {
            Edge *edge = graphEdges[j];
            int u = edge->get_vertex1();
            int v = edge->get_vertex2();
            int weight = edge->get_edge_weight();
            if (distance[v] > distance[u] + weight) {
                delete[] distance;
                delete[] parent;
            }
        }
    }
    for (int j = 0; j < edges; ++j) {
        delete graphEdges[j];
    }
    delete[] graphEdges;
}




//=============================================================================================
//                                     ALGORYTM  PRIMA
//=============================================================================================

// MST - minimalne drzewo rozpinające (graf nieskierowany)
// MST zawiera wszystkie wierzchołki grafu i podzbiór jego krawędzi
// MST grafu to jego podgraf z którego usunięto niektóre krawędzie (aby nie było cykli)

void Graph_List::Prim_algorithm(int *&key, int *&parent, int startingVertex = 0) {
    //stos wierzchołków Prima (tzn. obiektów wierzchołek posiadających swój numer, oraz key)
    auto *heap = new Vertex_Min_Heap(vertices);
    heap->vertexes[startingVertex]->set_key(0);
    key[startingVertex] = 0;
    parent[startingVertex] = -1;
    while (heap->has_elements()) {
        //tworzymy stos (aby mieć wierzchołek o najmniejszej wadze), trzeba co pętlę ponieważ w pętli zmieniają się elementy stosu
        heap->create_min_heap();
        Vertex *vertexU = heap->extract_min();
        //neighbourTraverse - obiekt (ListElement) za pomocą którego dobieramy się do wszystkich sąsiadów wierzchołka z listy sąsiedztwa
        auto neighbourTraverse = adjacency_list[vertexU->get_vertex_index()]->get_head();
        while (neighbourTraverse != nullptr) {
            int neighbour = neighbourTraverse->neighbour;
            if (heap->is_in_heap(neighbour)) {
                int edgeWeight = neighbourTraverse->edge_weight;
                int neighbourPosition = heap->position[neighbour];
                if (edgeWeight < heap->vertexes[neighbourPosition]->get_key()) {
                    heap->vertexes[neighbourPosition]->set_key(edgeWeight);
                    key[neighbour] = edgeWeight;
                    parent[neighbour] = vertexU->get_vertex_index();
                }
            }
            neighbourTraverse = neighbourTraverse->next;
        }
    }
    delete heap;
}




//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================





int Graph_List::get_vertices() {
    return vertices;
}

int Graph_List::get_edges() {
    return edges;
}