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

    for (int i = 0; i < edge_count; i++) {

        //TODO add edges
    }

    return *graph;
}



//=============================================================================================
//                                     ALGORYTM  DIJKSTRY
//=============================================================================================

// algorytm Dijkstry służy do wyznaczania najkrótszej drogi
// pomędzy wierzchołkiem startowym do wszystkich wierzchołków

void Graph_Matrix::dijkstra_algorithm(int source, int destination) {

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

    while (vertices->getSize() != 0) {
        int i = vertices->pop();
        for (size_t j = 0; j < vertex_count; j++) {
            if (incidence_matrix[i][j] > 0 && distance[j] > distance[i] + incidence_matrix[i][j]) {
                distance[j] = distance[i] + incidence_matrix[i][j];
                markedVertices[j] = i;
            }
        }
    }

    int currentVertex = destination;
    if (distance[currentVertex] == INT_MAX)
        return; //throws error

    cout << "\n\nShortest path for incidence matrix representation"
         << "\n--------------------------------------------------" << endl;

    while (currentVertex != -1) {
        cout << currentVertex;
        currentVertex = markedVertices[currentVertex];
        if (currentVertex != -1)
            cout << "<-";
        else
            cout << "\n";
    }

    cout << "\nTotal cost: " << distance[destination] << endl;

    delete[] markedVertices;
    delete[] distance;
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

void Graph_Matrix::prim_algorithm() {
    int *MST = new int[vertex_count];
    int *key = new int[vertex_count];
    bool *visited = new bool[vertex_count];
    int totalCost = 0;

    for (size_t i = 0; i < vertex_count; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
    }

    key[0] = 0;
    MST[0] = -1;

    for (size_t count = 0; count < vertex_count - 1; count++) {
        int j = min_key(key, visited);

        visited[j] = true;

        for (size_t i = 0; i < vertex_count; i++) {
            if (incidence_matrix[j][i] && visited[i] == false && incidence_matrix[j][i] < key[i]) {
                MST[i] = j;
                key[i] = incidence_matrix[j][i];
            }
        }
    }

    cout << "\n\nMinimal Spanning Tree for incidence matrix representation (Prims's algorithm)"
         << "\n------------------------------------------------------------------------------" << endl;
    for (size_t i = 1; i < vertex_count; i++) {
        cout << "Edge " << MST[i] << " -> " << i << " weight: " << incidence_matrix[i][MST[i]] << endl;
        totalCost += incidence_matrix[i][MST[i]];
    }
    cout << "\nTotal cost: " << totalCost << endl;

    delete[] MST;
    delete[] key;
    delete[] visited;
}


int Graph_Matrix::min_key(int *key, bool *visited) {
    int min = INT_MAX, min_index;

    for (size_t i = 0; i < vertex_count; i++)
        if (visited[i] == false && key[i] < min)
            min = key[i], min_index = i;

    return min_index;
}



//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================

void Graph_Matrix::kruskal_algorithm() {
    size_t i, j;
    int k, a, b, u, v, count = 1;
    int min, totalCost = 0;
    int **cost = new int *[vertex_count];
    int *parent = new int[vertex_count];

    for (i = 0; i < vertex_count; i++) {
        parent[i] = 0;
        cost[i] = new int[vertex_count];

        for (j = 0; j < vertex_count; j++) {
            if (incidence_matrix[i][j] == 0)
                cost[i][j] = INT_MAX;
            else
                cost[i][j] = incidence_matrix[i][j];
        }
    }

    cout << "\n\nMinimal Spanning Tree for incidence matrix representation (Kruskal's algorithm)"
         << "\n--------------------------------------------------------------------------------" << endl;

    while (count < vertex_count) {
        for (i = 0, min = INT_MAX; i < vertex_count; i++) {
            for (j = 0; j < vertex_count; j++) {
                if (cost[i][j] < min) {
                    min = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find(u, parent);
        v = find(v, parent);
        if (unify(u, v, parent)) {
            cout << "Edge " << a << " -> " << b << " weight: " << min << endl;;
            totalCost += min;
            count++;
        }
        cost[a][b] = cost[b][a] = INT_MAX;
    }
    cout << "\nTotal cost: " << totalCost;

    for (i = 0; i < vertex_count; i++)
        delete[] cost[i];
    delete[] parent;
}


int Graph_Matrix::find(int i, int *parent) {
    while (parent[i])
        i = parent[i];
    return i;
}

int Graph_Matrix::unify(int i, int j, int *parent) {
    if (i != j) {
        parent[j] = i;
        return 1;
    }
    return 0;
}