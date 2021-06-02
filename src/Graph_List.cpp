#include "Graph_List.h"
#include <iostream>
#include <iomanip>
using namespace std;


/*-----------------------------LISTA SĄSIEDZTWA-----------------------------

        ----------
       |          |          ------                 ------
       |   V1  <--|-------  |  V4  |  <----------  |  V3  |  <----------   ...
       |          |          ------                 ------
       |          |
       |          |          ------                 ------
       |   V2  <--|-------  |  V5  |  <----------  |  V8  |  <----------   ...
       |          |          ------                 ------
       |          |
       |          |          ------                 ------
       |   V3  <--|-------  |  V6  |  <----------  |  V1  |  <----------   ...
       |          |          ------                 ------
       |          |
        ----------

            ^
            |
   lista wskaźników na listy


*/


Graph_List::Graph_List(int vertexes) {
    this->vertices = vertexes;
    edges = 0;
    adjacency_list = new Adjacency_List *[vertexes];
    for (int i = 0; i < vertexes; ++i) {
        adjacency_list[i] = new Adjacency_List();
    }
}

Graph_List::~Graph_List() {
    for (int i = 0; i < vertices; ++i)
        delete adjacency_list[i];
    delete[] adjacency_list;
}


void Graph_List::add_edge(int vertex1, int vertex2, int edge_weight, bool directed) {

    if (directed) {
        adjacency_list[vertex1]->add_edge(vertex2, edge_weight);
        ++edges;
    }
    else {
        adjacency_list[vertex1]->add_edge(vertex2, edge_weight);
        adjacency_list[vertex2]->add_edge(vertex1, edge_weight);
        ++edges;
    }
}

void Graph_List::print() {
    for (int i = 0; i < vertices; ++i) {
        cout << "  V " << i << ":";
        auto list = adjacency_list[i]->get_head();
        while (list != nullptr) {
            cout << setw(8) << list->neighbour << " (" << list->edge_weight << ")";
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
// algorytm pracuje na grafach skierowanych

// idea: tworzenie kolejki priorytetowej wierzchołków i dokonanie relaksacji
//       dla każdego wierzchołka usuniętego z tej kolejki

void Graph_List::Dijkstra_algorithm(int *&distance, int *&parent, int starting_vertex) {

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
        Vertex *vertex_min = heap->extract_min();

        // tworzymy obiekt za pomocą którego mamy dostęp do wszystkich sąsiadów danego wierzchołka
        auto check_neighbours = adjacency_list[vertex_min->get_vertex_index()]->get_head();

       // dla wszystkich sąsiadów wierzchołka
        while (check_neighbours != nullptr) {

            int neighbour = check_neighbours->neighbour;        // ustawienie sąsiada
            int edge_weight = check_neighbours->edge_weight;    // ustawienie wagi krawędzi
            int neighbour_position = heap->position[neighbour]; // ustawienie pozycji sąsiada
            int distanceU = vertex_min->get_element();                          // dystans do wierzchołka U
            int distanceV = heap->vertexes[neighbour_position]->get_element();  // dystans do wierzchołka V

            // dokonujemy relaksacji krawędzi - sprawdzenie, czy przy przejściu daną
            // krawędzią grafu nie otrzymamy krótszej ścieżki niż dotychczasowa
            if (distanceV > distanceU + edge_weight) {
                heap->vertexes[neighbour_position]->set_element(distanceU + edge_weight);
                distance[neighbour] = distanceU + edge_weight;
                parent[neighbour] = vertex_min->get_vertex_index();
            }
            // przechodzimy do kolejnego sąsiada
            check_neighbours = check_neighbours->next;
        }
    }

    delete heap;
}



void Graph_List::Dijkstra() {

    int *distance = new int[vertices];  // odległość od wierzchołka startowego
    int *parent = new int[vertices];    // wierzchołek poprzedzający
    int start;

    cout << "\n podaj wierzcholek poczatkowy ";
    cin >> start;

    if (start < 0 || start >= vertices) {
        cout << " zly wierzcholek";
        return;
    }

    Dijkstra_algorithm(distance, parent, start);

    cout << "\n algorytm Dijkstry listowo: (wierzcholek: <- (poprzednicy) [dystans]\n";
    for (int i = 0; i < vertices; ++i) {
        cout << "  " << i << ": ";

        int x = i;
        int c = 0;
        while (parent[x] > 0 && parent[x] < vertices && parent[x] != start) {
            cout << " <- (" << parent[x] <<")";
            x = parent[x];
            c++;
        }
        if (i == start)
            cout <<" <- start" << endl;
        else if (c == 0 && (distance[i] > 10000000 || distance[i] < -10000000))  // gdy jest jakiś śmieć w distance[i]
            cout <<" <- nieosiagalny" << endl;
        else
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

bool Graph_List::Bellman_Ford_algorithm(int *&distance, int *&parent, int starting_vertex) {

    Edge **graph_edges = new Edge *[edges];  // zbiór krawędzi

    // ustawienie początkowych wartości
    int i = 0;
    for (int j = 0; j < vertices; ++j) {

        distance[j] = INT_MAX / 2;  // dystans = inf
        parent[j] = -1;             // poprzednik nieokreślony

        // pobieranie głowy listy
        auto check_neighbours = adjacency_list[j]->get_head();

        // dla każdego wierzchołka
        while (check_neighbours != nullptr) {

            // dodanie do zbioru nowej krawędzi wychodzącej z tego wierzchołka
            graph_edges[i] = new Edge(j, check_neighbours->neighbour, check_neighbours->edge_weight);
            ++i;

            // przejście do kolejnego wierzchołka
            check_neighbours = check_neighbours->next;
        }
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
            int U = edge->get_vertex1();           // wierzchołek początkowy
            int V = edge->get_vertex2();           // wierzchołek końcowy
            int weight = edge->get_edge_weight();  // waga

            // dokonujemy relaksacji krawędzi - sprawdzenie, czy przy przejściu daną
            // krawędzią grafu nie otrzymamy krótszej ścieżki niż dotychczasowa
            if (distance[V] > distance[U] + weight) {
                distance[V] = distance[U] + weight;
                parent[V] = U;
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



void Graph_List::Bellman_Ford() {

    int *distance = new int[vertices];  // odległość od wierzchołka startowego
    int *parent = new int[vertices];    // wierzchołek poprzedzający
    int start;

    cout << "\n podaj wierzcholek poczatkowy ";
    cin >> start;

    if (start < 0 || start >= vertices) {
        cout << " zly wierzcholek";
        return;
    }

    bool bf = Bellman_Ford_algorithm(distance, parent, start);

    // jeżeli wykryto cykl o ujemnej wadze - z założenia krawędzie mogą mieć ujemną wagę
    if (!bf) {
        cout << "\n Wykryto cykl o ujemnej wadze\n";
    } else {
        cout << "\n algorytm Bellmana-Forda listowo: (wierzcholek: <- (poprzednicy) [dystans]\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "  " << i << ": ";

            int x = i;
            int c = 0;
            while (parent[x] > 0 && parent[x] < vertices && parent[x] != start) {
                cout << " <- (" << parent[x] <<")";
                x = parent[x];
                c++;
            }
            if (i == start)
                cout <<" <- start" << endl;
            else if (c == 0 && (distance[i] > 10000000 || distance[i] < -10000000))  // gdy jest jakiś śmieć w distance[i]
                cout <<" <- nieosiagalny" << endl;
            else
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

void Graph_List::Prim_algorithm(int *&key, int *&parent) {

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

        // tworzymy obiekt za pomocą którego mamy dostęp do wszystkich sąsiadów danego wierzchołka
        auto check_neighbours = adjacency_list[vertexU->get_vertex_index()]->get_head();

        // dla wszystkich sąsiadów wierzchołka
        while (check_neighbours != nullptr) {

            int neighbour = check_neighbours->neighbour;  // ustawienie sąsiada

            // sprawdzamy czy sąsiad wierzchołka należy do kolejki
            // (wierzchołek został już z kolejki usunięty)
            if (heap->is_in_heap(neighbour)) {
                int edge_weight = check_neighbours->edge_weight;      // ustawienie wagi krawędzi
                int neighbour_position = heap->position[neighbour];   // ustawienie pozycji sąsiada

                // sprawdzamy czy waga krawędzi jest mniejsza od klucza/wagi
                if (edge_weight < heap->vertexes[neighbour_position]->get_element()) {

                    // coś w rodzaju relaksacji
                    // aktualizujemy krawędź oraz jej wagę
                    heap->vertexes[neighbour_position]->set_element(edge_weight);
                    key[neighbour] = edge_weight;
                    parent[neighbour] = vertexU->get_vertex_index();
                }
            }
            // przechodzimy do kolejnego sąsiada
            check_neighbours = check_neighbours->next;
        }
    }
    delete heap;
}



void Graph_List::Prim() {

    int *key = new int[vertices];       // klucze
    int *parent = new int[vertices];    // wierzchołek poprzedzający
    int sum = 0;

    Prim_algorithm(key, parent);

    cout << "\n algorytm Prima listowo: krawedzie MST: (wierzcholek1 - wierzcholek2 : waga)\n";
    for (int i = 0; i < vertices; ++i) {
        if (parent[i] != -1) {
            cout << "  " << i << " - " << parent[i] << " : " << key[i] << "\n";
            sum += key[i];
        }
    }
    cout << "   waga calkowita MST: " << sum << endl;

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

void Graph_List::Kruskal_algorithm(Edge **mst_edges) {

    int *parent = new int[vertices];  // wierzchołek poprzedzający
    int *rank = new int[vertices];
    int graph_edge_index = 0;
    Edge **graph_edges = new Edge *[2 * edges];  // [2*edges] ponieważ będą duplikaty krawędzi


    // sortujemy niemalejąco wagi które składają się na graf
    for (int j = 0; j < vertices; ++j) {

        // przy okazji uzupełniamy dane startowe
        parent[j] = j;
        rank[j] = 0;

        // tworzymy obiekt za pomocą którego mamy dostęp do wszystkich sąsiadów danego wierzchołka
        auto check_neighbours = adjacency_list[j]->get_head();

        // dla wszystkich sąsiadów wierzchołka
        while (check_neighbours != nullptr) {

            // tworzymy zmienne pomocnicze
            graph_edges[graph_edge_index] = new Edge(j, check_neighbours->neighbour, check_neighbours->edge_weight);
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
            check_neighbours = check_neighbours->next;
        }
    }
    int mst_edge_index = 0;  // indeks MST

    // wykonujemy dla wszystkich krawędzi
    for (graph_edge_index = 0; graph_edge_index < 2 * edges; ++graph_edge_index) {

        // pobieramy krawędź
        Edge *edge = graph_edges[graph_edge_index];

        int U = edge->get_vertex1();              // wierzchołek początkowy
        int V = edge->get_vertex2();              // wierzchołek końcowy
        int set1 = kruskal_find_setL(parent, U);  // poddrzewo dla wierzchołka początkowego
        int set2 = kruskal_find_setL(parent, V);  // poddrzewo dla wierzchołka końcowego

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



void Graph_List::Kruskal() {

    Edge **mst_edges = new Edge *[vertices - 1];  // gotowe krawędzie MST
    int sum = 0;

    // dla każdego wierzchołka
    for (int i = 0; i < vertices - 1; i++) {

        // tworzymy poddrzewo tego wierzchołka
        mst_edges[i] = new Edge(0, 0, 0);
    }

    Kruskal_algorithm(mst_edges);

    cout << "\n algorytm Kruskala listowo: krawedzie MST: (wierzcholek1 - wierzcholek2 : waga)\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << "  " << mst_edges[i]->get_vertex1() << " - " << mst_edges[i]->get_vertex2() << " : "
             << mst_edges[i]->get_edge_weight() << "\n";
        sum += mst_edges[i]->get_edge_weight();
    }
    cout << "   waga calkowita MST: " << sum << endl;

    for (int i = 0; i < vertices - 1; ++i) {
        delete mst_edges[i];
    }
    delete[] mst_edges;
}



// szukanie poddrzewa
int Graph_List::kruskal_find_setL(int *parent, int x) {

    if (parent[x] != x)
        parent[x] = kruskal_find_setL(parent, parent[x]);
    return parent[x];
}
