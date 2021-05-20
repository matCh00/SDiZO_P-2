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
    cout << "E:    ";
    for (int i = 0; i < edges; ++i) {
        cout << "\t" << edge_weights[i];
    }
    cout << "\n\n";
    incidence_matrix->print();
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

void Graph_Matrix::Bellman_Ford_algorithm(int startingVertex) {
    int *distance = new int[vertices];
    int *parent = new int[vertices];

    for (int i = 0; i < vertices; ++i) {
        distance[i] = INT_MAX / 2;
        parent[i] = -1;
    }
    parent[startingVertex] = startingVertex;
    distance[startingVertex] = 0;
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
        cout << "Wykryto cykl o lacznej ujemnej wadze\n";
    } else {
        cout << "Algorytm Bellmana-Forda macierzowo; Wierzcholek: distance/parent\n";
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

void Graph_Matrix::Prim_algorithm(int *&key, int *&parent, int start_vertex) {
    //stos wierzchołków Prima (tzn. obiektów wierzchołek posiadających swój numer, oraz key)
    auto *heap = new Vertex_Min_Heap(vertices);
    heap->vertexes[start_vertex]->set_key(0);
    key[start_vertex] = 0;
    parent[start_vertex] = -1;
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
                            if (edgeWeight < heap->vertexes[neighbourPosition]->get_key()) {
                                heap->vertexes[neighbourPosition]->set_key(edgeWeight);
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
    delete heap;
}



//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================





int Graph_Matrix::get_vertices() {
    return vertices;
}

int Graph_Matrix::get_edges() {
    return edges;
}