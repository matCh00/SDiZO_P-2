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


// tworzenie grafu - reprezentacja macierzowa (dzidziczenie po obiekcie Graph)
Graph_Matrix::Graph_Matrix(int vertexes, int edges, bool directed) {

    vertex_count = vertexes;    // liczba wierzchołków
    edge_count = 0;             // liczba krawędzi - inkrementacja w funkcji print
    this->directed = directed;

    // uzupełnianie macierzy zerami (pusty graf)
    for (int v = 0; v < vertex_count; v++) {

        vector<int> temp;
        for (int e = 0; e < edges; e++) {
            temp.push_back(0);
        }

        incidence_matrix.push_back(temp);
    }
}


// usuwanie grafu
Graph_Matrix::~Graph_Matrix() {

    // usuwanie wszystkich wierszy (wszystkich elementów)
    for (int v = 0; v < vertex_count; v++) {
        incidence_matrix[v].clear();
        incidence_matrix[v].shrink_to_fit();
    }
    incidence_matrix.clear();   // usuwanie wskaźnika na macierz incydencji
}


// wypisanie grafu w postaci macierzy
void Graph_Matrix::print() {

    cout << "Graf - macierz: " << endl << endl;

    for (int v = 0; v < incidence_matrix.size(); v++) {
        for (int e = 0; e < incidence_matrix[v].size(); e++)
            cout << setw(4) << incidence_matrix[v][e] << "  ";

        cout << endl;
    }
}


// dodanie krawędzi
void Graph_Matrix::add_edge(int origin, int destination, int weight) {

    if (origin >= 0 && origin < vertex_count && destination >= 0 && destination < vertex_count) {
        incidence_matrix[origin][edge_count] = 1 * weight;   // [wierzchołek początkowy] [krawędź]

        if (directed)
            incidence_matrix[destination][edge_count] = -1 * weight;  //  [wierzchołek końcowy] [krawędź]
        else
            incidence_matrix[destination][edge_count] = 1 * weight;   //  [wierzchołek końcowy] [krawędź]

        edge_count++;
    }
    else
        cout << "Blad podczas dodawania krawedzi";
}


// losowe generowanie grafu
Graph_Matrix Graph_Matrix::random(int vertexes, float density, bool directed){

    int ed;

    if (directed)
        ed = vertexes * (vertexes - 1);
    else
        ed = (vertexes * (vertexes - 1)) / 2;


    int edg = (int)(density * ed / 100);

    Graph_Matrix *graph = new Graph_Matrix(vertexes, edg, directed);

    //TODO add edges

    return *graph;
}
