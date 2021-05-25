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
            " -----------------------------------------------------------\n\n\n";

    bool run = true;

    while (run) {

        cout << "[1]  -  SPF  (algorytmy Dijkstry i Bellmana-Forda)\n"
                "[2]  -  MST  (algorytmy Prima i Kruskala)\n"
                "[3]  -  testy efektywnosci algorytmow grafowych\n"
                "[0]  -  wyjscie\n";

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

        cout << "\n[1]  -  wczytaj graf\n"
                "[2]  -  wygeneruj graf\n"
                "[3]  -  wyswietl graf\n"
                "[4]  -  algorytm Dijkstry\n"
                "[5]  -  algorytm Bellmana-Forda\n"
                "[0]  -  wyjdz\n";

        int choose;
        cin >> choose;

        switch (choose) {

            case 1: {
                cout << "Podaj nazwe pliku: ";
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
                    cout << "Blad podczas otwierania pliku\n";
                file.close();
                break;
            }

            case 2:
                int ve, de;
                cout << "podaj liczbe wierzcholkow: ";
                cin >> ve;
                cout << "podaj gestosc: ";
                cin >> de;

                delete graph_list;
                graph_list = new Graph_List(ve);
                delete graph_matrix;
                graph_matrix = new Graph_Matrix(ve);

                generate_edges(ve, de, graph_list, graph_matrix, true);
                break;

            case 3:
                cout << "\nGraf w postaci listy \n";
                graph_list->print();
                cout << endl << endl;
                cout << "Graf w postaci macierzy \n";
                graph_matrix->print();
                break;

            case 4:
                graph_list->Dijkstra_algorithm();
                graph_matrix->Dijkstra_algorithm();
                break;

            case 5:
                graph_list->Bellman_Ford_algorithm();
                graph_matrix->Bellman_Ford_algorithm();
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

        cout << "\n[1]  -  wczytaj graf\n"
                "[2]  -  wygeneruj graf\n"
                "[3]  -  wyswietl graf\n"
                "[4]  -  algorytm Prima\n"
                "[5]  -  algorytm Kruskala\n"
                "[0]  -  wyjdz\n";

        int choose;
        cin >> choose;

        switch (choose) {

            case 1: {
                cout << "Podaj nazwe pliku: ";
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
                    cout << "Blad podczas otwierania pliku\n";
                file.close();
                break;
            }

            case 2:
                int ve, de;
                cout << "podaj liczbe wierzcholkow: "; cin >> ve;
                cout << "podaj gestosc: "; cin >> de;

                delete graph_list;
                graph_list = new Graph_List(ve);
                delete graph_matrix;
                graph_matrix = new Graph_Matrix(ve);

                generate_edges(ve, de, graph_list, graph_matrix, false);
                break;

            case 3:
                cout << "\nGraf w postaci listy \n";
                graph_list->print();
                cout << endl << endl;
                cout << "Graf w postaci macierzy \n";
                graph_matrix->print();
                break;

            case 4:
                graph_list->Prim_algorithm();
                graph_matrix->Prim_algorithm();
                break;

            case 5:
                graph_list->Kruskal_algorithm();
                graph_matrix->Kruskal_algorithm();
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

    bool run = true;

    while (run) {

        cout << "[1] - Dijkstra, [2] - Bellman-Ford, [3] - Prim, [4] - Kruskal (x1 - lista, x2 - macierz np 32 - Prim macierz), [0] - wyjdz" << endl;
        int alg;
        cin >> alg;

        int v;
        float d;
        int number;
        double final_time = 0;


        cout << "liczba wierzcholkow "; cin >> v;
        cout << "gestosc "; cin >> d;
        cout << "liczba powtorzen "; cin >> number;


        for (int i = 0; i < number; i++) {

            Graph_List *graph_list = new Graph_List(v);
            Graph_Matrix *graph_matrix = new Graph_Matrix(v);

            if (alg == 1 || alg == 2){
                generate_edges(v, d, graph_list, graph_matrix, true);
            }
            if (alg == 3 || alg == 4){
                generate_edges(v, d, graph_list, graph_matrix, false);
            }

            switch (alg) {

                case 11:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Dijkstra_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time += (double)time1.count();

                    break;
                }

                case 12:{

                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Dijkstra_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time += (double)time2.count();

                    break;
                }

                case 21:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Bellman_Ford_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time += (double)time1.count();

                    break;
                }

                case 22:{

                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Bellman_Ford_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time += (double)time2.count();

                    break;
                }

                case 31:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Prim_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time += (double)time1.count();

                    break;
                }

                case 32:{

                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Prim_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time += (double)time2.count();

                    break;
                }

                case 41:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Kruskal_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time += (double)time1.count();

                    break;
                }

                case 42:{

                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Kruskal_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time += (double)time2.count();

                    break;
                }

                case 0:
                    run = false;
                    break;

                default:
                    run = false;
                    break;
            }
        }

        ofstream measurement;
        measurement.open("RESULT.txt", ios::app);

        measurement << endl << "ID algorytmu: " << alg << " wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time << endl << "średnia: " << setprecision(10) << final_time / number << endl << endl;

        measurement.close();
    }
}

