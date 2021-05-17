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

    incidence_matrix = new int *[vertex_count];

    // uzupełnianie macierzy zerami (pusty graf)
    for (int i = 0; i < vertexes; i++) {
        incidence_matrix[i] = new int[vertex_count];

        for (int j = 0; j < edges; j++)
            incidence_matrix[i][j] = 0;
    }
}


// usuwanie grafu
Graph_Matrix::~Graph_Matrix() {

    // usuwanie wszystkich wierszy (wszystkich elementów)
    for (int i = 0; i < vertex_count; i++)
        delete[] incidence_matrix[i];

    delete[] incidence_matrix;
}


// wypisanie grafu w postaci macierzy
void Graph_Matrix::print() {

    cout << "Graf - macierz: " << endl << endl;

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++)
            cout << setw(4) << incidence_matrix[i][j] << "  ";

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