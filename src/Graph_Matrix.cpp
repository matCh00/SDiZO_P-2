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


Graph_Matrix::Graph_Matrix(int vertexes) {
    this->vertices = vertexes;
    edges = 0;
    edge_weights = new int[edges];
    incidence_matrix = new Incidence_Matrix(0, vertexes);
}

Graph_Matrix::~Graph_Matrix() {
    delete incidence_matrix;
    delete[] edge_weights;
}


void Graph_Matrix::add_edge(int vertex1, int vertex2, int weight, bool directed) {

    if (directed) {
        incidence_matrix->add_column();
        incidence_matrix->set_new_edge(vertex1, 1);
        incidence_matrix->set_new_edge(vertex2, -1);
        new_edge_weights(weight);
        ++edges;
    }
    else {
        incidence_matrix->add_column();
        incidence_matrix->set_new_edge(vertex1, 1);
        incidence_matrix->set_new_edge(vertex2, 1);
        new_edge_weights(weight);
        ++edges;
    }
}

void Graph_Matrix::new_edge_weights(int added_weight) {
    int *new_edge_weights = new int[edges + 1];
    for (int i = 0; i < edges; ++i) {
        new_edge_weights[i] = edge_weights[i];
    }
    new_edge_weights[edges] = added_weight;
    delete[] edge_weights;
    edge_weights = new_edge_weights;
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
// algorytm pracuje na grafach skierowanych

// idea: tworzenie kolejki priorytetowej wierzchołków i dokonanie relaksacji
//       dla każdego wierzchołka usuniętego z tej kolejki

void Graph_Matrix::Dijkstra_algorithm(int *&distance, int *&parent, int starting_vertex) {

    // kolejka priorytetowa - kopiec minimalny wierzchołków (każdy przechowuje wartość i dystans)
    auto *heap = new Vertex_Min_Heap(vertices);

    heap->vertexes[starting_vertex]->set_element(0);  // ustawianie początkowego wierzchołka w kopcu
    distance[starting_vertex] = 0;   // dystans = 0
    parent[starting_vertex] = -1;    // poprzednik nieokreślony

    // dla każdego wierzchołka
    while (heap->has_elements()) {

        // tworzymy / aktualizujemy kopiec minimalny
        heap->create_min_heap();

        // wybieramy wierzchołek o najmniejszej wartości i usuwamy go z kolejki
        Vertex *vertexU = heap->extract_min();

        // ustawiamy wartość wybranego wierzchołka
        int vertex_number = vertexU->get_vertex_index();

        // spośród wszystkich krawędzi
        for (int U = 0; U < edges; ++U) {

            // szukamy wierzchołek startowy (początek krawędzi == 1)
            if (incidence_matrix->get(U, vertex_number) == 1) {

                int edge_weight = edge_weights[U];   // waga krawędzi

                // spośród wszystkich wierzchołków
                for (int V = 0; V < vertices; ++V) {

                    // szukamy sąsiada (wierzchołek końcowy krawędzi == -1)
                    // V jest sąsiadem U
                    if (incidence_matrix->get(U, V) == -1) {

                        int neighbour_position = heap->position[V];                        // ustawienie pozycji sąsiada
                        int distanceU = vertexU->get_element();                            // dystans do wierzchołka U
                        int distanceV = heap->vertexes[neighbour_position]->get_element(); // dystans do wierzchołka V

                        // dokonujemy relaksacji krawędzi - sprawdzenie, czy przy przejściu daną
                        // krawędzią grafu nie otrzymamy krótszej ścieżki niż dotychczasowa
                        if (distanceV > distanceU + edge_weight) {
                            heap->vertexes[neighbour_position]->set_element(distanceU + edge_weight);
                            distance[V] = distanceU + edge_weight;
                            parent[V] = vertexU->get_vertex_index();
                        }
                        break;
                    }
                }
            }
        }
    }

    delete heap;
}



void Graph_Matrix::Dijkstra() {

    int *distance = new int[vertices];  // odległość od wierzchołka startowego
    int *parent = new int[vertices];    // wierzchołek poprzedzający
    int start = 0;
/*
    cout << "\npodaj wierzcholek poczatkowy";
    cin >> start;

    if (start < 0 || start >= vertices) {
        cout << "zly wierzcholek";
        return;
    }
*/
    Dijkstra_algorithm(distance, parent, start);

    cout << "\nalgorytm Dijkstry macierzowo: (wierzcholek: <- (poprzednicy) [dystans]\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": ";

        int x = i;
        while (parent[x] > 0 && parent[x] < vertices && parent[x] != start) {
            cout << " <- (" << parent[x] <<")";
            x = parent[x];
        }
        cout <<" <- (" << start << ")  [" << distance[i] << "]" << endl;
    }

    delete[] distance;
    delete [] parent;
}



//=============================================================================================
//                               ALGORYTM  FORDA-BELLMANA
//=============================================================================================

// algorytm Forda-Bellmana służy do wyznaczania najkrótszej drogi pomędzy wierzchołkiem startowym
// do wszystkich wierzchołków w porównaniu do Dijkstry opiera się na metodzie relaksacji
// nie opiera się na założeniu że wagi w grafie są nieujemne
// algorytm pracuje na grafach skierowanych

// idea: relaksacja następuje (wierzchołki - 1) razy każdej krawędzi

bool Graph_Matrix::Bellman_Ford_algorithm(int *&distance, int *&parent, int starting_vertex) {

    for (int i = 0; i < vertices; ++i) {
        distance[i] = INT_MAX / 2;  // dystans = inf
        parent[i] = -1;             // poprzednik nieokreślony
    }

    int graph_edge_index = 0;
    Edge **graph_edges = new Edge *[edges];  // zbiór krawędzi

    // dla każdej krawędzi
    for (int i = 0; i < edges; ++i) {

        int vertex1 = 0;
        int vertex2 = 0;

        // szukamy wierzchołka początkowego (v == 1)
        for (int j = 0; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex1 = j;
                break;
            }
        }
        // szukamy wierzchołka końcowego (v == -1)
        for (int j = 0; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == -1) {
                vertex2 = j;
                break;
            }
        }

        // dodajemy do zbioru nową krawędź o wierzchołkach znalezionych powyżej
        graph_edges[graph_edge_index] = new Edge(vertex1, vertex2, edge_weights[i]);
        ++graph_edge_index;
    }

    parent[starting_vertex] = starting_vertex;
    distance[starting_vertex] = 0;
    bool relaxed = true;

    // (liczba wierzchołków - 1) razy
    for (int x = 1; x < vertices && relaxed; ++x) {
        relaxed = false;

        // (liczba krawędzi) razy
        for (int y = 0; y < edges; ++y) {

            Edge *edge = graph_edges[y];           // krawędź
            int u = edge->get_vertex1();           // wierzchołek początkowy
            int v = edge->get_vertex2();           // wierzchołek końcowy
            int weight = edge->get_edge_weight();  // waga

            // dokonujemy relaksacji krawędzi - sprawdzenie, czy przy przejściu daną
            // krawędzią grafu nie otrzymamy krótszej ścieżki niż dotychczasowa
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                relaxed = true;
            }
        }
    }

    if (relaxed) {
        for (int j = 0; j < edges; ++j) {
            Edge *edge = graph_edges[j];
            int u = edge->get_vertex1();
            int v = edge->get_vertex2();
            int weight = edge->get_edge_weight();
            if (distance[v] > distance[u] + weight) {
                delete[] distance;
                delete[] parent;
                return false;
            }
        }
    }
    for (int j = 0; j < edges; ++j) {
        delete graph_edges[j];
    }

    delete[] graph_edges;
    return true;
}



void Graph_Matrix::Bellman_Ford() {

    int *distance = new int[vertices];  // odległość od wierzchołka startowego
    int *parent = new int[vertices];    // wierzchołek poprzedzający
    int start = 0;
/*
    cout << "\npodaj wierzcholek poczatkowy";
    cin >> start;

    if (start < 0 || start >= vertices) {
        cout << "zly wierzcholek";
        return;
    }
*/
    bool bf = Bellman_Ford_algorithm(distance, parent, start);

    // jeżeli wykryto cykl o ujemnej wadze - z założenia krawędzie mogą mieć ujemną wagę
    if (!bf) {
        cout << "\nWykryto cykl o ujemnej wadze\n";
    }
    else {
        cout << "\nalgorytm Bellmana-Forda macierzowo: (wierzcholek: <- (poprzednicy) [dystans]\n";
        for (int i = 0; i < vertices; ++i) {
            cout << i << ": ";

            int x = i;
            while (parent[x] > 0 && parent[x] < vertices && parent[x] != start) {
                cout << " <- (" << parent[x] <<")";
                x = parent[x];
            }
            cout <<" <- (" << start << ")  [" << distance[i] << "]" << endl;
        }
    }

    delete[] distance;
    delete[] parent;
}



//=============================================================================================
//                                     ALGORYTM  PRIMA
//=============================================================================================

// algorytm Prima służy do wyznaczania minimalnego drzewa rozpinającego
// MST zawiera wszystkie wierzchołki grafu i podzbiór jego krawędzi
// MST grafu to jego podgraf z którego usunięto niektóre krawędzie (aby nie było cykli)
// algorytm pracuje na grafach nieskierowanych

// idea: tworzenie kolejki priorytetowej wierzchołków oraz listę wierzchołków rozpatrzonych,
//       wybieranie krawędzi o najmniejszej wadze dodając wierzchołki do listy wierzchołków
//       rozpatrzonych i dodawanie krawędzi do zbioru MST aż lista wierzchołków rozpatrzonych
//       nie będzie zawierała wszystkich wierzchołków

void Graph_Matrix::Prim_algorithm(int *&key, int *&parent) {

    // kolejka priorytetowa - kopiec minimalny wierzchołków (każdy przechowuje wartość i klucz/wagę)
    auto *heap = new Vertex_Min_Heap(vertices);

    heap->vertexes[0]->set_element(0);  // ustawianie początkowego wierzchołka w kopcu
    key[0] = 0;        // klucz/waga = 0
    parent[0] = -1;    // poprzednik nieokreślony

    // dla każdego wierzchołka
    while (heap->has_elements()) {

        // tworzymy / aktualizujemy kopiec minimalny
        heap->create_min_heap();

        // wybieramy wierzchołek o najmniejszej wartości i usuwamy go z kolejki
        Vertex *vertexU = heap->extract_min();

        // ustawiamy wartość wybranego wierzchołka
        int vertex_number = vertexU->get_vertex_index();

        // spośród wszystkich krawędzi
        for (int U = 0; U < edges; ++U) {

            // szukamy wierzchołek startowy (początek krawędzi == 1)
            if (incidence_matrix->get(U, vertex_number) == 1) {

                int edge_weight = edge_weights[U];  // waga krawędzi

                // spośród wszystkich wierzchołków
                for (int V = 0; V < vertices; ++V) {

                    // szukamy sąsiada (wierzchołek końcowy krawędzi == 1)
                    // V jest sąsiadem U
                    if (incidence_matrix->get(U, V) == 1 && V != vertex_number) {

                        // sprawdzamy czy sąsiad wierzchołka należy do kolejki
                        // (wierzchołek został już z kolejki usunięty)
                        if (heap->is_in_heap(V)) {

                            int neighbour_position = heap->position[V];  // ustawienie sąsiada

                            // sprawdzamy czy waga krawędzi jest mniejsza od klucza/wagi
                            if (edge_weight < heap->vertexes[neighbour_position]->get_element()) {

                                // coś w rodzaju relaksacji
                                // aktualizujemy krawędź oraz jej wagę
                                heap->vertexes[neighbour_position]->set_element(edge_weight);
                                key[V] = edge_weight;
                                parent[V] = vertexU->get_vertex_index();
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



void Graph_Matrix::Prim() {

    int *key = new int[vertices];       // klucze
    int *parent = new int[vertices];    // wierzchołek poprzedzający

    Prim_algorithm(key, parent);

    cout << "\nalgorytm Prima macierzowo: krawedzie MST: (wierzcholek - poprzednik : waga)\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << i << " - " << parent[i] << " : " << key[i] << "\n";
        }
    }

    delete[] key;
    delete[] parent;
}



//=============================================================================================
//                                     ALGORYTM  KRUSKALA
//=============================================================================================

// algorytm Kruskala służy do wyznaczania minimalnego drzewa rozpinającego
// MST zawiera wszystkie wierzchołki grafu i podzbiór jego krawędzi
// MST grafu to jego podgraf z którego usunięto niektóre krawędzie (aby nie było cykli)
// algorytm pracuje na grafach nieskierowanych

// idea: dla każdego wierzchołka tworzymy jego poddrzewo, sortujemy krawędzie niemalejąco,
//       sprawdzamy czy wierzchołki tworzące krawędź należą do różnych poddrzew,
//       jeżeli tak to dodajemy krawędź do MST

void Graph_Matrix::Kruskal_algorithm(Edge **mst_edges) {

    int *parent = new int[vertices];  // wierzchołek poprzedzający
    int *rank = new int[vertices];
    int graph_edge_index = 0;
    int mst_edge_index = 0;
    Edge **graph_edges = new Edge *[edges];

    // uzupełniamy dane startowe
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    // sortujemy niemalejąco wagi które składają się na graf
    for (int i = 0; i < edges; ++i) {

        int vertex1 = 0;  // wierzchołek początkowy
        int vertex2 = 0;  // wierzchołek końcowy
        int j = 0;

        // szukamy wierzchołka początkowego (v == 1)
        for (j; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex1 = j;
                ++j;
                break;
            }
        }
        // szukamy wierzchołka początkowego (v == 1)
        for (j; j < edges; ++j) {
            if (incidence_matrix->get(i, j) == 1) {
                vertex2 = j;
                break;
            }
        }

        // tworzymy zmienne pomocnicze
        graph_edges[graph_edge_index] = new Edge(vertex1, vertex2, edge_weights[i]);
        Edge *swap = graph_edges[graph_edge_index];
        int k = graph_edge_index - 1;

        // przesuwanie elementów (dokonujemy sortowania krawędzi)
        while (k >= 0 && graph_edges[k]->get_edge_weight() > swap->get_edge_weight()) {
            graph_edges[k + 1] = graph_edges[k];
            --k;
        }
        // dodanie na koniec
        graph_edges[k + 1] = swap;
        ++graph_edge_index;
    }

    // wykonujemy dla wszystkich krawędzi
    for (graph_edge_index = 0; graph_edge_index < edges; ++graph_edge_index) {

        // pobieramy krawędź
        Edge *edge = graph_edges[graph_edge_index];

        int U = edge->get_vertex1();              // wierzchołek początkowy
        int V = edge->get_vertex2();              // wierzchołek końcowy
        int set1 = kruskal_find_setM(parent, U);  // poddrzewo dla wierzchołka początkowego
        int set2 = kruskal_find_setM(parent, V);  // poddrzewo dla wierzchołka końcowego

        // sprawdzamy czy wierzchołki danej krawędzi należą do dwóch różnych poddrzew
        // jeżeli należą do różnych poddrzew to
        if (set1 != set2) {

            // dodajemy krawędź do rozwiązania
            mst_edges[mst_edge_index]->set_vertex1(U);
            mst_edges[mst_edge_index]->set_vertex2(V);
            mst_edges[mst_edge_index]->set_edge_weight(edge->get_edge_weight());
            ++mst_edge_index;

            // UNION - łączymy dwa poddrzewa w jedno
            if (rank[set1] < rank[set2])
                parent[set1] = set2;
            else
                parent[set2] = set1;
            if (rank[set1] == rank[set2])
                ++rank[set1];
        }
        delete graph_edges[graph_edge_index];
    }

    delete[] parent;
    delete[] rank;
    delete[] graph_edges;
}



void Graph_Matrix::Kruskal() {

    Edge **mst_edges = new Edge *[vertices - 1];  // gotowe krawędzie MST

    // dla każdego wierzchołka
    for (int i = 0; i < vertices-1; i++) {

        // tworzymy poddrzewo tego wierzchołka
        mst_edges[i] = new Edge(0, 0, 0);
    }

    Kruskal_algorithm(mst_edges);

    cout << "\nalgorytm Kruskala macierzowo: krawedzie MST: (wierzcholek - nastepnik : waga)\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << mst_edges[i]->get_vertex1() << " - " << mst_edges[i]->get_vertex2() << " : "
             << mst_edges[i]->get_edge_weight()
             << "\n";
    }

    for (int i = 0; i < vertices - 1; ++i) {
        delete mst_edges[i];
    }
    delete[] mst_edges;
}



// szukanie poddrzewa
int Graph_Matrix::kruskal_find_setM(int *parent, int x) {

    if (parent[x] != x)
        parent[x] = kruskal_find_setM(parent, parent[x]);
    return parent[x];
}

