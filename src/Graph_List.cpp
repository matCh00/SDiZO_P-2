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

void Graph_List::dijkstra_algorithm(int source, int destination) {
    if (destination >= vertex_count)
        return; //throws error

    int *distance = new int[vertex_count];
    int *markedVertices = new int[vertex_count];

    for (size_t i = 0; i < vertex_count; i++) {
        distance[i] = INT_MAX;
        markedVertices[i] = -1;
    }

    distance[source] = 0;

    Min_Heap *vertices = new Min_Heap();
    for (size_t i = 0; i < vertex_count; i++) {
        vertices->push(i);
    }

    Node *node;
    while (vertices->getSize() != 0) {
        int i = vertices->pop();
        node = adjacency_list[i];

        while (node) {
            if (node->weight > 0 && distance[node->vertex] > distance[i] + node->weight) {
                distance[node->vertex] = distance[i] + node->weight;
                markedVertices[node->vertex] = i;
            }

            node = node->next;
        }
    }

    int currentVertex = destination;
    if (distance[currentVertex] == INT_MAX)
        return; //throws error

    cout << "\n\nShortest path for adjacency list representation"
         << "\n------------------------------------------------" << endl;

    while (currentVertex != -1) {
        cout << currentVertex;
        currentVertex = markedVertices[currentVertex];
        if (currentVertex != -1)
            cout << "<-";
        else
            cout << "\n";
    }

    cout << "\nTotal cost: " << distance[destination] << endl;

    delete[] distance;
    delete[] markedVertices;
}





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

void Graph_List::prim_algorithm() {
    int *MST = new int[vertex_count];
    int *key = new int[vertex_count];
    int totalCost = 0;

    Min_Heap *vertices = new Min_Heap();

    for (size_t i = 0; i < vertex_count; i++) {
        key[i] = INT_MAX;
        MST[i] = -1;
        vertices->push(i);
    }

    key[0] = 0;

    Node *node;
    while (vertices->getSize() != 0) {
        int i = vertices->pop();
        node = adjacency_list[i];

        while (node) {
            if (vertices->find(node->vertex) && node->weight < key[node->vertex]) {
                key[node->vertex] = node->weight;
                MST[node->vertex] = i;
            }

            node = node->next;
        }
    }

    cout << "\n\nMinimal Spanning Tree for adjacency list representation (Prim's algorithm)"
         << "\n---------------------------------------------------------------------------" << endl;
    for (size_t i = 1; i < vertex_count; i++) {
        cout << "Edge " << MST[i] << " -> " << i << " weight: " << key[i] << endl;
        totalCost += key[i];
    }
    cout << "\nTotal cost: " << totalCost << endl;

    delete[] MST;
    delete[] key;
}




//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================

void Graph_List::kruskal_algorithm() {
    size_t i, j;
    int k, u, v, count = 1;
    int min, totalCost = 0;
    Node **cost = new Node *[vertex_count];

    for (i = 0; i < vertex_count; i++) {
        cost[i] = new Node[vertex_count];

        Node *node = adjacency_list[i];
        while (node) {
            if (node->weight == 0)
                cost[i]->weight = INT_MAX;
            else
                cost[i]->weight = node->weight;
            cost[i]->next = node->next;
            cost[i]->vertex = node->vertex;

            node = node->next;
        }
    }

    cout << "\n\nMinimal Spanning Tree for adjacency list representation (Kruskal's algorithm)"
         << "\n------------------------------------------------------------------------------" << endl;

    while (count < vertex_count) {
        for (i = 0, min = INT_MAX; i < vertex_count; i++) {
            Node *node = cost[i];
            while (node) {
                if (node->weight < min) {
                    min = node->weight;
                    u = i;
                    v = node->vertex;
                }

                node = node->next;
            }
        }

        if (u != v) {
            cout << "Edge " << u << " -> " << v << " weight: " << min << endl;;
            totalCost += min;
            count++;
        }

        Node *node = cost[u];
        while (node) {
            if (node->vertex == v)
                node->weight = INT_MAX;

            node = node->next;
        }

        node = cost[v];
        while (node) {
            if (node->vertex == u)
                node->weight = INT_MAX;

            node = node->next;
        }
    }
    cout << "\nTotal cost: " << totalCost;

    for (i = 0; i < vertex_count; i++)
        delete[] cost[i];
}
