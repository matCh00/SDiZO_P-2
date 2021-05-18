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

