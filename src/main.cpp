#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace chrono;


void generate_edges(int vertexes, float density, Graph_List *graph_list, Graph_Matrix *graph_matrix, bool directed) {

    // potrzebne do prawidłowego pseudolosowania danych
    srand((unsigned int)time(NULL));

    int possible_edges;

    // liczba możliwych krawędzi w zależności od ich typu
    if (directed){
        possible_edges = vertexes * (vertexes - 1);
    }
    if (directed == false) {
        possible_edges = vertexes * (vertexes - 1) / 2;
    }

    int edges = (int) ((float) possible_edges * density / 100);  // liczba krawędzi w grafie

    if (directed) {
        if (edges < vertexes) {
            edges = vertexes;
        }
    }
    if (directed == false) {
        if (edges < vertexes - 1) {
            edges = vertexes - 1;
        }
    }

    int *edge_weights = new int[edges];  // wagi krawędzi

    // losowanie wag krawędzi
    for (int i = 0; i < edges; ++i) {
        edge_weights[i] = 1 + rand() % (99 - 1 + 1);
    }

    Incidence_Matrix *matrix = new Incidence_Matrix(edges, vertexes);  // macierz
    int *vertices_array = new int[vertexes - 1];  // wierzchołki

    for (int i = 0; i < vertexes - 1; ++i) {
        vertices_array[i] = i + 1;
    }

    int vertex_start = 0;
    int vertex_end = 0;
    int edge_index = 0;

    // losowanie krawędzi - nowa zaczyna się tam gdzie skończyła się poprzednia aby dojść do wszystkich
    for (int i = vertexes - 1; i > 0; --i) {
        vertex_end = 0 + rand() % ((i - 1) - 0 + 1);  // losowy wierzchołek końcowy

        if (directed) {
            matrix->set(edge_index, vertex_start, 1);
            matrix->set(edge_index, vertices_array[vertex_end], -1);
            graph_list->add_edge(vertex_start, vertices_array[vertex_end], edge_weights[edge_index], true);
            graph_matrix->add_edge(vertex_start, vertices_array[vertex_end], edge_weights[edge_index], true);
        }
        if (directed == false) {
            matrix->set(edge_index, vertex_start, 1);
            matrix->set(edge_index, vertices_array[vertex_end], 1);
            graph_list->add_edge(vertex_start, vertices_array[vertex_end], edge_weights[edge_index], false);
            graph_matrix->add_edge(vertex_start, vertices_array[vertex_end], edge_weights[edge_index], false);
        }

        ++edge_index;
        vertex_start = vertices_array[vertex_end];  // następny wierzchołek to wierzchołek końcowy poprzedniej krawędzi
        vertices_array[vertex_end] = vertices_array[i - 1];
    }
    delete[] vertices_array;

    if (directed) {
        matrix->set(edge_index, vertex_start, 1);
        matrix->set(edge_index, 0, -1);
        graph_list->add_edge(vertex_start, 0, edge_weights[edge_index], true);
        graph_matrix->add_edge(vertex_start, 0, edge_weights[edge_index], true);
        ++edge_index;
    }

    int *edge_start = new int[possible_edges];
    int *edge_end = new int[possible_edges];
    int index = 0;

    if (directed) {
        for (int i = 0; i < vertexes; ++i) {
            for (int j = 0; j < vertexes; ++j) {
                if (i != j) {
                    edge_start[index] = i;
                    edge_end[index] = j;
                    ++index;
                }
            }
        }
    }
    if (directed == false) {
        for (int i = 0; i < vertexes; ++i) {
            for (int j = i + 1; j < vertexes; ++j) {
                edge_start[index] = i;
                ++index;
            }
        }
        index = 0;
        for (int i = 0; i < vertexes; ++i) {
            for (int j = i + 1; j < vertexes; ++j) {
                edge_end[index] = j;
                ++index;
            }
        }
    }


    // losowanie krawędzi - jeżeli istnieje to usuwamy ze zbioru możliwych do wygenerowania, jeżeli nie istnieje to dodajemy ją do grafu
    for (edge_index; edge_index < edges; ++edge_index) {
        int chosen_edge = 0 + rand() % ((possible_edges - 1) - 0 + 1);

        if (directed) {
            while (matrix->are_directed_connected(edge_start[chosen_edge], edge_end[chosen_edge])) {
                edge_start[chosen_edge] = edge_start[possible_edges - 1];
                edge_end[chosen_edge] = edge_end[possible_edges - 1];
                --possible_edges;
                chosen_edge = 0 + rand() % ((possible_edges - 1) - 0 + 1);
            }
            matrix->set(edge_index, edge_start[chosen_edge], 1);
            matrix->set(edge_index, edge_end[chosen_edge], -1);
            graph_list->add_edge(edge_start[chosen_edge], edge_end[chosen_edge], edge_weights[edge_index], true);
            graph_matrix->add_edge(edge_start[chosen_edge], edge_end[chosen_edge], edge_weights[edge_index], true);
            edge_start[chosen_edge] = edge_start[possible_edges - 1];
            edge_end[chosen_edge] = edge_end[possible_edges - 1];
            --possible_edges;
        }
        if (directed == false) {
            while (matrix->are_undirected_connected(edge_start[chosen_edge], edge_end[chosen_edge])) {
                edge_start[chosen_edge] = edge_start[possible_edges - 1];
                edge_end[chosen_edge] = edge_end[possible_edges - 1];
                --possible_edges;
                chosen_edge = 0 + rand() % ((possible_edges - 1) - 0 + 1);
            }
            matrix->set(edge_index, edge_start[chosen_edge], 1);
            matrix->set(edge_index, edge_end[chosen_edge], 11);
            graph_list->add_edge(edge_start[chosen_edge], edge_end[chosen_edge], edge_weights[edge_index], false);
            graph_matrix->add_edge(edge_start[chosen_edge], edge_end[chosen_edge], edge_weights[edge_index], false);
            edge_start[chosen_edge] = edge_start[possible_edges - 1];
            edge_end[chosen_edge] = edge_end[possible_edges - 1];
            --possible_edges;
        }

    }
    delete matrix;
    delete[] edge_weights;
    delete[] edge_start;
    delete[] edge_end;
}


void SPF();
void MST();
void algorithm_measurement();



int main() {

    cout << " -----------------------------------------------------------\n"
            "|             Projekt  SDiZO  -  Mateusz Chalik             |\n"
            "|                                                           |\n"
            "|         Badanie efektywnosci algorytmow grafowych         |\n"
            "|                         maj  2021                         |\n"
            " -----------------------------------------------------------\n\n";

    bool run = true;

    while (run) {

        cout << "\n [1]  -  SPF  (algorytmy Dijkstry i Bellmana-Forda)\n"
                " [2]  -  MST  (algorytmy Prima i Kruskala)\n"
                " [3]  -  testy efektywnosci algorytmow grafowych\n"
                " [0]  -  wyjscie\n";

        int option;
        cin >> option;

        switch (option) {

            case 1:
                SPF();
                break;

            case 2:
                MST();
                break;

            case 3:
                algorithm_measurement();
                break;

            case 0:
                run = false;
                break;

            default:
                break;
        }
    }

    return 0;
}



void SPF() {

    bool run = true;
    int v = 2;
    int e = 1;
    Graph_List *graph_list = new Graph_List(2);
    Graph_Matrix *graph_matrix = new Graph_Matrix(2);
    graph_list->add_edge(0, 1, 1, true);
    graph_matrix->add_edge(0, 1, 1, true);

    while (run) {

        cout << "\n [1]  -  wczytaj graf\n"
                " [2]  -  wygeneruj graf\n"
                " [3]  -  wyswietl graf\n"
                " [4]  -  algorytm Dijkstry\n"
                " [5]  -  algorytm Bellmana-Forda\n"
                " [0]  -  wyjdz\n";

        int choose;
        cin >> choose;

        switch (choose) {

            case 1: {
                cout << " Podaj nazwe pliku: ";
                int edgesNumber, verticesNumber;
                string file_name;
                cin >> file_name;

                fstream file;
                file.open(file_name);

                if (file.is_open()) {
                    delete graph_list;
                    delete graph_matrix;
                    file >> edgesNumber >> verticesNumber;
                    graph_list = new Graph_List(verticesNumber);
                    graph_matrix = new Graph_Matrix(verticesNumber);
                    int v1, v2, weight;
                    for (int j = 0; j < edgesNumber; ++j) {
                        file >> v1 >> v2 >> weight;
                        graph_list->add_edge(v1, v2, weight, true);
                        graph_matrix->add_edge(v1, v2, weight, true);
                    }
                } else
                    cout << " Blad podczas otwierania pliku\n";
                file.close();
                break;
            }

            case 2:
                int ve, de;
                cout << " podaj liczbe wierzcholkow: ";
                cin >> ve;
                cout << " podaj gestosc: ";
                cin >> de;

                delete graph_list;
                graph_list = new Graph_List(ve);
                delete graph_matrix;
                graph_matrix = new Graph_Matrix(ve);

                generate_edges(ve, de, graph_list, graph_matrix, true);
                break;

            case 3:
                cout << "\n Graf w postaci listy \n";
                graph_list->print();
                cout << endl << endl;
                cout << " Graf w postaci macierzy \n";
                graph_matrix->print();
                break;

            case 4:
                graph_list->Dijkstra();
                graph_matrix->Dijkstra();
                break;

            case 5:
                graph_list->Bellman_Ford();
                graph_matrix->Bellman_Ford();
                break;

            case 0:
                run = false;
                break;

            default:
                break;
        }
    }
}



void MST() {

    bool run = true;
    int v = 2;
    int e = 1;
    Graph_List *graph_list = new Graph_List(2);
    Graph_Matrix *graph_matrix = new Graph_Matrix(2);
    graph_list->add_edge(0, 1, 1, false);
    graph_matrix->add_edge(0, 1, 1, false);

    while (run) {

        cout << "\n [1]  -  wczytaj graf\n"
                " [2]  -  wygeneruj graf\n"
                " [3]  -  wyswietl graf\n"
                " [4]  -  algorytm Prima\n"
                " [5]  -  algorytm Kruskala\n"
                " [0]  -  wyjdz\n";

        int choose;
        cin >> choose;

        switch (choose) {

            case 1: {
                cout << " Podaj nazwe pliku: ";
                int edgesNumber, verticesNumber;
                string file_name;
                cin >> file_name;

                fstream file;
                file.open(file_name);

                if (file.is_open()) {
                    delete graph_list;
                    delete graph_matrix;
                    file >> edgesNumber >> verticesNumber;
                    graph_list = new Graph_List(verticesNumber);
                    graph_matrix = new Graph_Matrix(verticesNumber);
                    int v1, v2, weight;
                    for (int j = 0; j < edgesNumber; ++j) {
                        file >> v1 >> v2 >> weight;
                        graph_list->add_edge(v1, v2, weight, false);
                        graph_matrix->add_edge(v1, v2, weight, false);
                    }
                } else
                    cout << " Blad podczas otwierania pliku\n";
                file.close();
                break;
            }

            case 2:
                int ve, de;
                cout << " podaj liczbe wierzcholkow: "; cin >> ve;
                cout << " podaj gestosc: "; cin >> de;

                delete graph_list;
                graph_list = new Graph_List(ve);
                delete graph_matrix;
                graph_matrix = new Graph_Matrix(ve);

                generate_edges(ve, de, graph_list, graph_matrix, false);
                break;

            case 3:
                cout << "\n Graf w postaci listy \n";
                graph_list->print();
                cout << endl << endl;
                cout << " Graf w postaci macierzy \n";
                graph_matrix->print();
                break;

            case 4:
                graph_list->Prim();
                graph_matrix->Prim();
                break;

            case 5:
                graph_list->Kruskal();
                graph_matrix->Kruskal();
                break;

            case 0:
                run = false;
                break;

            default:
                break;
        }
    }
}



void algorithm_measurement(){

    Graph_List *graph_list;
    Graph_Matrix *graph_matrix;
    double final_time_list_1;
    double final_time_matrix_1;
    double final_time_list_2;
    double final_time_matrix_2;
    int number = 20;
    int v;
    float d;

    // tyle różnych kombinacji
    for (int i = 1; i <= 20; i++) {

        if (i == 1) {
            v = 20;
            d = 25;
        }
        else if (i == 2) {
            v = 20;
            d = 50;
        }
        else if (i == 3) {
            v = 20;
            d = 75;
        }
        else if (i == 4) {
            v = 20;
            d = 99;
        }
        else if (i == 5) {
            v = 40;
            d = 25;
        }
        else if (i == 6) {
            v = 40;
            d = 50;
        }
        else if (i == 7) {
            v = 40;
            d = 75;
        }
        else if (i == 8) {
            v = 40;
            d = 99;
        }
        else if (i == 9) {
            v = 60;
            d = 25;
        }
        else if (i == 10) {
            v = 60;
            d = 50;
        }
        else if (i == 11) {
            v = 60;
            d = 75;
        }
        else if (i == 12) {
            v = 60;
            d = 99;
        }
        else if (i == 13) {
            v = 80;
            d = 25;
        }
        else if (i == 14) {
            v = 80;
            d = 50;
        }
        else if (i == 15) {
            v = 80;
            d = 75;
        }
        else if (i == 16) {
            v = 80;
            d = 99;
        }
        else if (i == 17) {
            v = 100;
            d = 25;
        }
        else if (i == 18) {
            v = 100;
            d = 50;
        }
        else if (i == 19) {
            v = 100;
            d = 75;
        }
        else if (i == 20) {
            v = 100;
            d = 99;
        }
        else {
            cout << "error";
            return;
        }


        final_time_list_1 = 0;
        final_time_matrix_1 = 0;
        final_time_list_2 = 0;
        final_time_matrix_2 = 0;

        for (int n = 0; n < number; n++){

            graph_list = new Graph_List(v);
            graph_matrix = new Graph_Matrix(v);
            generate_edges(v, d, graph_list, graph_matrix, true);

            int *distance = new int[v];
            int *parent = new int[v];

            //początek pomiaru
            high_resolution_clock::time_point t1 = high_resolution_clock::now();

            graph_list->Dijkstra_algorithm(distance, parent, 0);

            //koniec pomiaru
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
            final_time_list_1 += (double)time1.count();

            delete[] distance;
            delete[] parent;
            distance = new int[v];
            parent = new int[v];

            //początek pomiaru
            high_resolution_clock::time_point t3 = high_resolution_clock::now();

            graph_matrix->Dijkstra_algorithm(distance, parent, 0);

            //koniec pomiaru
            high_resolution_clock::time_point t4 = high_resolution_clock::now();
            duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
            final_time_matrix_1 += (double)time2.count();

            delete[] distance;
            delete[] parent;
            distance = new int[v];
            parent = new int[v];

            //początek pomiaru
            high_resolution_clock::time_point t5 = high_resolution_clock::now();

            graph_list->Bellman_Ford_algorithm(distance, parent, 0);

            //koniec pomiaru
            high_resolution_clock::time_point t6 = high_resolution_clock::now();
            duration<double> time3 = duration_cast<duration<double>>(t6 - t5);
            final_time_list_2 += (double)time3.count();

            delete[] distance;
            delete[] parent;
            distance = new int[v];
            parent = new int[v];

            //początek pomiaru
            high_resolution_clock::time_point t7 = high_resolution_clock::now();

            graph_matrix->Bellman_Ford_algorithm(distance, parent, 0);

            //koniec pomiaru
            high_resolution_clock::time_point t8 = high_resolution_clock::now();
            duration<double> time4 = duration_cast<duration<double>>(t8 - t7);
            final_time_matrix_2 += (double)time4.count();

            delete[] distance;
            delete[] parent;
            delete graph_list;
            delete graph_matrix;
        }

        ofstream measurement;
        measurement.open("RESULT.txt", ios::app);

        measurement << endl << "List Dijkstra:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_list_1 << endl << "średnia: " << setprecision(10) << final_time_list_1 / number << endl << endl;

        measurement << endl << "Matrix Dijkstra:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_matrix_1 << endl << "średnia: " << setprecision(10) << final_time_matrix_1 / number << endl << endl;

        measurement << endl << "List Bellman-Ford:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_list_2 << endl << "średnia: " << setprecision(10) << final_time_list_2 / number << endl << endl;

        measurement << endl << "Matrix Bellman-Ford:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_matrix_2 << endl << "średnia: " << setprecision(10) << final_time_matrix_2 / number << endl << endl;

        measurement.close();



        final_time_list_1 = 0;
        final_time_matrix_1 = 0;
        final_time_list_2 = 0;
        final_time_matrix_2 = 0;

        for (int nn = 0; nn < number; nn++){

            graph_list = new Graph_List(v);
            graph_matrix = new Graph_Matrix(v);
            generate_edges(v, d, graph_list, graph_matrix, false);

            int *key = new int[v];
            int *parent = new int[v];
            Edge **mst_edges;

            //początek pomiaru
            high_resolution_clock::time_point t1 = high_resolution_clock::now();

            graph_list->Prim_algorithm(key, parent);

            //koniec pomiaru
            high_resolution_clock::time_point t2 = high_resolution_clock::now();
            duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
            final_time_list_1 += (double)time1.count();

            delete[] key;
            delete[] parent;
            key = new int[v];
            parent = new int[v];

            //początek pomiaru
            high_resolution_clock::time_point t3 = high_resolution_clock::now();

            graph_matrix->Prim_algorithm(key, parent);

            //koniec pomiaru
            high_resolution_clock::time_point t4 = high_resolution_clock::now();
            duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
            final_time_matrix_1 += (double)time2.count();

            delete[] key;
            delete[] parent;
            mst_edges = new Edge *[v - 1];
            for (int i = 0; i < v - 1; i++) {
                mst_edges[i] = new Edge(0, 0, 0);
            }

            //początek pomiaru
            high_resolution_clock::time_point t5 = high_resolution_clock::now();

            graph_list->Kruskal_algorithm(mst_edges);

            //koniec pomiaru
            high_resolution_clock::time_point t6 = high_resolution_clock::now();
            duration<double> time3 = duration_cast<duration<double>>(t6 - t5);
            final_time_list_2 += (double)time3.count();

            delete[] mst_edges;
            mst_edges = new Edge *[v - 1];
            for (int i = 0; i < v - 1; i++) {
                mst_edges[i] = new Edge(0, 0, 0);
            }

            //początek pomiaru
            high_resolution_clock::time_point t7 = high_resolution_clock::now();

            graph_matrix->Kruskal_algorithm(mst_edges);

            //koniec pomiaru
            high_resolution_clock::time_point t8 = high_resolution_clock::now();
            duration<double> time4 = duration_cast<duration<double>>(t8 - t7);
            final_time_matrix_2 += (double)time4.count();

            delete[] mst_edges;
            delete graph_list;
            delete graph_matrix;
        }

        measurement.open("RESULT.txt", ios::app);

        measurement << endl << "List Prim:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_list_1 << endl << "średnia: " << setprecision(10) << final_time_list_1 / number << endl << endl;

        measurement << endl << "Matrix Prim:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_matrix_1 << endl << "średnia: " << setprecision(10) << final_time_matrix_1 / number << endl << endl;

        measurement << endl << "List Kruskal:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_list_2 << endl << "średnia: " << setprecision(10) << final_time_list_2 / number << endl << endl;

        measurement << endl << "Matrix Kruskal:  wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_matrix_2 << endl << "średnia: " << setprecision(10) << final_time_matrix_2 / number << endl << endl;

        measurement.close();
    }
}

