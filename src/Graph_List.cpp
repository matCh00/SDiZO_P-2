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
        cout << "V " << i << ":";
        auto list = adjacency_list[i]->get_head();
        while (list != nullptr) {
            cout << setw(7) << list->neighbour << " (" << list->edge_weight << ")";
            list = list->next;
        }
        cout << "\n";
    }
}


//=============================================================================================
//                                     ALGORYTM  DIJKSTRY
//=============================================================================================

// algorytm Dijkstry służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków

void Graph_List::Dijkstra_algorithm() {
    int *distance = new int[vertices];
    int *parent = new int[vertices];

    //stos wierzchołków Dijkstry (tzn. obiektów wierzchołek posiadających swój numer, oraz distance)
    auto *heap = new Vertex_Min_Heap(vertices);
    heap->vertexes[0]->set_element(0);
    distance[0] = 0;
    parent[0] = -1;
    while (heap->has_elements()) {
        //tworzymy stos (aby mieć wierzchołek o najmniejszym dystansie), trzeba co pętlę ponieważ w pętli zmieniają się elementy stosu
        heap->create_min_heap();
        Vertex *vertexU = heap->extract_min();
        //neighbourTraverse - obiekt (ListElement) za pomocą którego dobieramy się do wszystkich sąsiadów wierzchołka z listy sąsiedztwa
        auto neighbourTraverse = adjacency_list[vertexU->get_vertex_index()]->get_head();
        while (neighbourTraverse != nullptr) {
            int neighbour = neighbourTraverse->neighbour;
            int edgeWeight = neighbourTraverse->edge_weight;
            int neighbourPosition = heap->position[neighbour];
            int distanceU = vertexU->get_element();
            int distanceV = heap->vertexes[neighbourPosition]->get_element();
            if (distanceV > distanceU + edgeWeight) {
                heap->vertexes[neighbourPosition]->set_element(distanceU + edgeWeight);
                distance[neighbour] = distanceU + edgeWeight;
                parent[neighbour] = vertexU->get_vertex_index();
            }
            neighbourTraverse = neighbourTraverse->next;
        }
    }

    cout << "Algorytm Dijkstry listowo; Wierzcholek: distance/parent\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": " << distance[i] << "/" << parent[i] << "\n";
    }

    delete heap;
}





//=============================================================================================
//                               ALGORYTM  FORDA-BELLMANA
//=============================================================================================

// algorytm Forda-Bellmana służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków
// w porównaniu do Dijkstry opiera się na metodzie relaksacji
// nie opiera się na założeniu że wagi w grafie są nieujemne

void Graph_List::Bellman_Ford_algorithm() {
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
    parent[0] = 0;
    distance[0] = 0;
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

    delete[] distance;
    delete[] parent;
    delete[] graphEdges;
}




//=============================================================================================
//                                     ALGORYTM  PRIMA
//=============================================================================================

// MST - minimalne drzewo rozpinające (graf nieskierowany)
// MST zawiera wszystkie wierzchołki grafu i podzbiór jego krawędzi
// MST grafu to jego podgraf z którego usunięto niektóre krawędzie (aby nie było cykli)

void Graph_List::Prim_algorithm() {
    int *key = new int[vertices];
    int *parent = new int[vertices];
    //stos wierzchołków Prima (tzn. obiektów wierzchołek posiadających swój numer, oraz key)
    auto *heap = new Vertex_Min_Heap(vertices);
    heap->vertexes[0]->set_element(0);
    key[0] = 0;
    parent[0] = -1;
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
                if (edgeWeight < heap->vertexes[neighbourPosition]->get_element()) {
                    heap->vertexes[neighbourPosition]->set_element(edgeWeight);
                    key[neighbour] = edgeWeight;
                    parent[neighbour] = vertexU->get_vertex_index();
                }
            }
            neighbourTraverse = neighbourTraverse->next;
        }
    }

    cout << "Algorytm Prima listowo; wierzcholek: key/parent\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": " << key[i] << "/" << parent[i] << "\n";
    }
    cout << "\nKrawedzie MST:\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : Waga = " << key[i] << "\n";
        }
    }

    delete[] key;
    delete[] parent;
    delete heap;
}




//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================

void Graph_List::Kruskal_algorithm() {
    Edge **mstEdges = new Edge *[vertices - 1];
    for (int i = 0; i < vertices-1; i++)
    {
        mstEdges[i] = new Edge(0,0,0);
    }

    int *parent = new int[vertices];
    int *rank = new int[vertices];
    Edge **graphEdges = new Edge *[2 * edges]; //2*edges bo będziemy mieć duplikaty krawędzi
    int graphEdgeIndex = 0;
    //tworzenie pomocniczych obiektów - krawędzi oraz ich sortowanie metodą insertionsort
    for (int j = 0; j < vertices; ++j) {
        parent[j] = j;
        rank[j] = 0;
        auto listTraverse = adjacency_list[j]->get_head();
        while (listTraverse != nullptr) {
            graphEdges[graphEdgeIndex] = new Edge(j, listTraverse->neighbour, listTraverse->edge_weight);
            Edge *swap = graphEdges[graphEdgeIndex];
            int k = graphEdgeIndex - 1;
            while (k >= 0 && graphEdges[k]->get_edge_weight() > swap->get_edge_weight()) {
                graphEdges[k + 1] = graphEdges[k];
                --k;
            }
            graphEdges[k + 1] = swap;
            ++graphEdgeIndex;
            listTraverse = listTraverse->next;
        }
    }
    int mstEdgeIndex = 0;
    for (graphEdgeIndex = 0; graphEdgeIndex < 2 * edges; ++graphEdgeIndex) {
        Edge *edge = graphEdges[graphEdgeIndex];
        int v1 = edge->get_vertex1();
        int v2 = edge->get_vertex2();
        int set1 = kruskal_find_setL(parent, v1);
        int set2 = kruskal_find_setL(parent, v2);
        if (set1 != set2) {
            mstEdges[mstEdgeIndex]->set_vertex1(v1);
            mstEdges[mstEdgeIndex]->set_vertex2(v2);
            mstEdges[mstEdgeIndex]->set_edge_weight(edge->get_edge_weight());
            ++mstEdgeIndex;
            if (rank[set1] < rank[set2])
                parent[set1] = set2;
            else
                parent[set2] = set1;
            if (rank[set1] == rank[set2])
                ++rank[set1];
        }
        delete graphEdges[graphEdgeIndex];
    }

    cout << "Algorytm Kruskala listowo; krawedzie MST:\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << mstEdges[i]->get_vertex1() << " - " << mstEdges[i]->get_vertex2() << " : Waga = "
             << mstEdges[i]->get_edge_weight()
             << "\n";
    }

    for (int i = 0; i < vertices - 1; ++i) {
        delete mstEdges[i];
    }
    delete[] mstEdges;
    delete[] parent;
    delete[] rank;
    delete[] graphEdges;
}




int Graph_List::kruskal_find_setL(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = kruskal_find_setL(parent, parent[x]);
    return parent[x];
}

int Graph_List::get_vertices() {
    return vertices;
}

int Graph_List::get_edges() {
    return edges;
}