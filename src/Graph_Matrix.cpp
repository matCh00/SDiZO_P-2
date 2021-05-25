#include "Graph_Matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;


/*---------------------------------MACIERZ INCYDENCJI---------------------------------
        \ krawędzie
          \
wierzchołki \     |    E1   |    E2   |    E3   |    E4   |    E5   |
              ----|--------------------------------------------------
                  |         |         |         |         |         |
              V1  |    1    |   -3    |    0    |    2    |    0    |         A[i,j] = 0 gdy nie ma połączenia
                  |         |         |         |         |         |
              ----|--------------------------------------------------         A[i,j] = 1 gdy Vi jest początkiem Ej
                  |         |         |         |         |         |
              V2  |    -1   |    0    |    0    |    0    |    9    |         A[i,j] = -1 gdy Vi jest końcem Ej
                  |         |         |         |         |         |
              ----|--------------------------------------------------
                  |         |         |         |         |         |       wagi krawędzi są pomnożone przez 0 / 1 / -1
              V3  |    0    |    0    |    1    |    -2   |    -9   |
                  |         |         |         |         |         |
             --------------------------------------------------------
                  |         |         |         |         |         |
              V4  |    0    |    3    |    -1   |    0    |    0    |
                  |         |         |         |         |         |
             --------------------------------------------------------

 */


Graph_Matrix::Graph_Matrix(int vertices) {
    this->vertices = vertices;
    edges = 0;
    edge_weights = new int[edges];
    incidence_matrix = new Incidence_Matrix(0, vertices);
}

Graph_Matrix::~Graph_Matrix() {
    delete incidence_matrix;
    delete[] edge_weights;
}

void Graph_Matrix::add_undirected_edge(int vertex1, int vertex2, int weight) {
    incidence_matrix->add_column();
    incidence_matrix->set_new_edge(vertex1, 1);
    incidence_matrix->set_new_edge(vertex2, 1);
    new_edge_weights(weight);
    ++edges;
}

void Graph_Matrix::add_directed_edge(int vertex1, int vertex2, int weight) {
    incidence_matrix->add_column();
    incidence_matrix->set_new_edge(vertex1, 1);
    incidence_matrix->set_new_edge(vertex2, -1);
    new_edge_weights(weight);
    ++edges;
}

void Graph_Matrix::new_edge_weights(int added_weight) {
    int *newEdgeWeights = new int[edges + 1];
    for (int i = 0; i < edges; ++i) {
        newEdgeWeights[i] = edge_weights[i];
    }
    newEdgeWeights[edges] = added_weight;
    delete[] edge_weights;
    edge_weights = newEdgeWeights;
}

void Graph_Matrix::print() {

    for (int y = 0; y < incidence_matrix->size_y; ++y) {
        cout << "V " << y << ":";
        for (int x = 0; x < incidence_matrix->size_x; ++x) {
            cout << setw(7) << incidence_matrix->array[x][y] * edge_weights[x];
        }
        cout << "\n";
    }
    cout << "\n";
}




//=============================================================================================
//                                     ALGORYTM  DIJKSTRY
//=============================================================================================

// algorytm Dijkstry służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków

void Graph_Matrix::Dijkstra_algorithm() {
    int *distance = new int[vertices];
    int *parent = new int[vertices];

    auto *heap = new Vertex_Min_Heap(vertices);
    heap->vertexes[0]->set_element(0);
    distance[0] = 0;
    parent[0] = -1;
    while (heap->has_elements()) {
        heap->create_min_heap();
        Vertex *vertexU = heap->extract_min();
        int vertexNumber = vertexU->get_vertex_index();
        for (int i = 0; i < edges; ++i) {
            if (incidence_matrix->get(i, vertexNumber) == 1) {
                int edgeWeight = edge_weights[i];
                for (int j = 0; j < vertices; ++j) {
                    if (incidence_matrix->get(i, j) == -1) {
                        // 'j' to sąsiad (neighbour)
                        int neighbourPosition = heap->position[j];
                        int distanceU = vertexU->get_element();
                        int distanceV = heap->vertexes[neighbourPosition]->get_element();
                        if (distanceV > distanceU + edgeWeight) {
                            heap->vertexes[neighbourPosition]->set_element(distanceU + edgeWeight);
                            distance[j] = distanceU + edgeWeight;
                            parent[j] = vertexU->get_vertex_index();
                        }
                        break;
                    }
                }
            }
        }
    }

    cout << "\nalgorytm Dijkstry macierzowo: (wierzcholek: dystans/poprzednik)\n";
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

void Graph_Matrix::Bellman_Ford_algorithm() {
    int *distance = new int[vertices];
    int *parent = new int[vertices];

    for (int i = 0; i < vertices; ++i) {
        distance[i] = INT_MAX / 2;
        parent[i] = -1;
    }
    parent[0] = 0;
    distance[0] = 0;
    Edge **graphEdges = new Edge *[edges];
    int graphEdgeIndex = 0;
    for (int i = 0; i < edges; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
        for (int j = 0; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex1 = j;
                break;
            }
        }
        for (int j = 0; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == -1) {
                vertex2 = j;
                break;
            }
        }
        graphEdges[graphEdgeIndex] = new Edge(vertex1, vertex2, edge_weights[i]);
        ++graphEdgeIndex;
    }
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
        cout << "\nWykryto cykl o ujemnej wadze\n";
    }
    else {
        cout << "\nalgorytm Bellmana-Forda macierzowo: (wierzcholek: dystans/poprzednik)\n";
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

void Graph_Matrix::Prim_algorithm() {
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
        int vertexNumber = vertexU->get_vertex_index();
        for (int i = 0; i < edges; ++i) {
            if (incidence_matrix->get(i, vertexNumber) == 1) {
                int edgeWeight = edge_weights[i];
                for (int j = 0; j < vertices; ++j) {
                    if (incidence_matrix->get(i, j) == 1 && j != vertexNumber) {
                        // 'j' to sąsiad (neighbour)
                        if (heap->is_in_heap(j)) {
                            int neighbourPosition = heap->position[j];
                            if (edgeWeight < heap->vertexes[neighbourPosition]->get_element()) {
                                heap->vertexes[neighbourPosition]->set_element(edgeWeight);
                                key[j] = edgeWeight;
                                parent[j] = vertexU->get_vertex_index();
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    cout << "\nalgorytm Prima macierzowo: (wierzcholek: klucz/poprzednik)\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": " << key[i] << "/" << parent[i] << "\n";
    }
    cout << "\nkrawedzie MST: (wierzcholek - poprzednik : waga)\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : " << key[i] << "\n";
        }
    }

    delete[] key;
    delete[] parent;
    delete heap;
}



//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================

void Graph_Matrix::Kruskal_algorithm() {
    Edge **mstEdges = new Edge *[vertices - 1];
    for (int i = 0; i < vertices-1; i++)
    {
        mstEdges[i] = new Edge(0,0,0);
    }

    int *parent = new int[vertices];
    int *rank = new int[vertices];
    Edge **graphEdges = new Edge *[edges];
    int graphEdgeIndex = 0;
    int mstEdgeIndex = 0;
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
    //tworzenie pomocniczych obiektów - krawędzi oraz ich sortowanie metodą insertionsort
    for (int i = 0; i < edges; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
        int j = 0;
        for (; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex1 = j;
                ++j;
                break;
            }
        }
        for (; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex2 = j;
                break;
            }
        }
        graphEdges[graphEdgeIndex] = new Edge(vertex1, vertex2, edge_weights[i]);
        Edge *swap = graphEdges[graphEdgeIndex];
        int k = graphEdgeIndex - 1;
        while (k >= 0 && graphEdges[k]->get_edge_weight() > swap->get_edge_weight()) {
            graphEdges[k + 1] = graphEdges[k];
            --k;
        }
        graphEdges[k + 1] = swap;
        ++graphEdgeIndex;
    }
    for (graphEdgeIndex = 0; graphEdgeIndex < edges; ++graphEdgeIndex) {
        Edge *edge = graphEdges[graphEdgeIndex];
        int v1 = edge->get_vertex1();
        int v2 = edge->get_vertex2();
        int set1 = kruskal_find_setM(parent, v1);
        int set2 = kruskal_find_setM(parent, v2);
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

    cout << "\nalgorytm Kruskala macierzowo: krawedzie MST: (wierzcholek - nastepnik : waga)\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << mstEdges[i]->get_vertex1() << " - " << mstEdges[i]->get_vertex2() << " : "
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


int Graph_Matrix::kruskal_find_setM(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = kruskal_find_setM(parent, parent[x]);
    return parent[x];
}

