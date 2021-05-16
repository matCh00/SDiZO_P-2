#include "Graph_Matrix.h"


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
Graph_Matrix::Graph_Matrix(int size, bool directed) : Graph(size, directed) {

    // uzupełnianie macierzy zerami (pusty graf)
    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++)
            incidence_matrix[i][j] = 0;
    }
}


// usuwanie grafu
Graph_Matrix::~Graph_Matrix() {

    // usuwanie wszystkich wierszy (wszystkich elementów)
    for (int i = 0; i < vertex_array.size(); i++) {
        incidence_matrix[i].clear();
        incidence_matrix[i].shrink_to_fit();
    }
    incidence_matrix.clear();   // usuwanie wskaźnika na macierz incydencji
}