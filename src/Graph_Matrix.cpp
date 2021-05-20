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




//=============================================================================================
//                                     ALGORYTM  DIJKSTRY
//=============================================================================================

// algorytm Dijkstry służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków

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

