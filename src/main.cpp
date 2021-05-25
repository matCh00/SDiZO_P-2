#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace chrono;


void generate_edges(int vertices, float density, Graph_List *graph_list, Graph_Matrix *graph_matrix, bool directed) {

    srand((unsigned int)time(NULL));

    int possibleEdges;

    if (directed){
        possibleEdges = vertices * (vertices - 1);
    }
    if (directed == false) {
        possibleEdges = vertices * (vertices - 1) / 2;
    }

    int edges = (int) ((float) possibleEdges * density / 100);

    if (directed) {
        if (edges < vertices) {
            edges = vertices;
        }
    }
    if (directed == false) {
        if (edges < vertices - 1) {
            edges = vertices  - 1;
        }
    }

    int *edgeWeights = new int[edges];
    for (int i = 0; i < edges; ++i) {
        edgeWeights[i] = 1 + rand() % (99 - 1 + 1);
    }
    Incidence_Matrix *matrix = new Incidence_Matrix(edges, vertices);
    int *verticesArray = new int[vertices - 1];
    for (int i = 0; i < vertices - 1; ++i) {
        verticesArray[i] = i + 1;
    }

    int vertexStart = 0;
    int vertexEnd = 0;
    int edgeIndex = 0;

    // losowanie krawędzi - nowa zaczyna się tam gdzie skończyła się poprzednia aby dojść do wszystkich
    for (int i = vertices - 1; i > 0; --i) {
        vertexEnd =  0 + rand() % ((i - 1) - 0 + 1);

        if (directed) {
            matrix->set(edgeIndex, vertexStart, 1);
            matrix->set(edgeIndex, verticesArray[vertexEnd], -1);
            graph_list->add_directed_edge(vertexStart, verticesArray[vertexEnd], edgeWeights[edgeIndex]);
            graph_matrix->add_directed_edge(vertexStart, verticesArray[vertexEnd], edgeWeights[edgeIndex]);
        }
        if (directed == false) {
            matrix->set(edgeIndex, vertexStart, 1);
            matrix->set(edgeIndex, verticesArray[vertexEnd], 1);
            graph_list->add_undirected_edge(vertexStart, verticesArray[vertexEnd], edgeWeights[edgeIndex]);
            graph_matrix->add_undirected_edge(vertexStart, verticesArray[vertexEnd], edgeWeights[edgeIndex]);
        }

        ++edgeIndex;
        vertexStart = verticesArray[vertexEnd];
        verticesArray[vertexEnd] = verticesArray[i - 1];
    }
    delete[] verticesArray;

    if (directed) {
        matrix->set(edgeIndex, vertexStart, 1);
        matrix->set(edgeIndex, 0, -1);
        graph_list->add_directed_edge(vertexStart, 0, edgeWeights[edgeIndex]);
        graph_matrix->add_directed_edge(vertexStart, 0, edgeWeights[edgeIndex]);
        ++edgeIndex;
    }

    int *edgeStart = new int[possibleEdges];
    int *edgeEnd = new int[possibleEdges];
    int index = 0;

    if (directed) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (i != j) {
                    edgeStart[index] = i;
                    edgeEnd[index] = j;
                    ++index;
                }
            }
        }
    }
    if (directed == false) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                edgeStart[index] = i;
                ++index;
            }
        }
        index = 0;
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                edgeEnd[index] = j;
                ++index;
            }
        }
    }


    // losowanie krawędzi - jeżeli istnieje to usuwamy ze zbioru możliwych do wygenerowania, jeżeli nie istnieje to dodajemy ją do grafu
    for (; edgeIndex < edges; ++edgeIndex) {
        int chosenEdge =  0 + rand() % ((possibleEdges - 1) - 0 + 1);

        if (directed) {
            while (matrix->are_directed_connected(edgeStart[chosenEdge], edgeEnd[chosenEdge])) {
                edgeStart[chosenEdge] = edgeStart[possibleEdges - 1];
                edgeEnd[chosenEdge] = edgeEnd[possibleEdges - 1];
                --possibleEdges;
                chosenEdge =  0 + rand() % ((possibleEdges - 1) - 0 + 1);
            }
            matrix->set(edgeIndex, edgeStart[chosenEdge], 1);
            matrix->set(edgeIndex, edgeEnd[chosenEdge], -1);
            graph_list->add_directed_edge(edgeStart[chosenEdge], edgeEnd[chosenEdge], edgeWeights[edgeIndex]);
            graph_matrix->add_directed_edge(edgeStart[chosenEdge], edgeEnd[chosenEdge], edgeWeights[edgeIndex]);
            edgeStart[chosenEdge] = edgeStart[possibleEdges - 1];
            edgeEnd[chosenEdge] = edgeEnd[possibleEdges - 1];
            --possibleEdges;
        }
        if (directed == false) {
            while (matrix->are_undirected_connected(edgeStart[chosenEdge], edgeEnd[chosenEdge])) {
                edgeStart[chosenEdge] = edgeStart[possibleEdges - 1];
                edgeEnd[chosenEdge] = edgeEnd[possibleEdges - 1];
                --possibleEdges;
                chosenEdge =  0 + rand() % ((possibleEdges - 1) - 0 + 1);
            }
            matrix->set(edgeIndex, edgeStart[chosenEdge], 1);
            matrix->set(edgeIndex, edgeEnd[chosenEdge], 11);
            graph_list->add_undirected_edge(edgeStart[chosenEdge], edgeEnd[chosenEdge], edgeWeights[edgeIndex]);
            graph_matrix->add_undirected_edge(edgeStart[chosenEdge], edgeEnd[chosenEdge], edgeWeights[edgeIndex]);
            edgeStart[chosenEdge] = edgeStart[possibleEdges - 1];
            edgeEnd[chosenEdge] = edgeEnd[possibleEdges - 1];
            --possibleEdges;
        }

    }
    delete matrix;
    delete[] edgeWeights;
    delete[] edgeStart;
    delete[] edgeEnd;
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
    graph_list->add_directed_edge(0, 1, 1);
    graph_matrix->add_directed_edge(0, 1, 1);

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
                        graph_list->add_directed_edge(v1, v2, weight);
                        graph_matrix->add_directed_edge(v1, v2, weight);
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
    graph_list->add_undirected_edge(0, 1, 1);
    graph_matrix->add_undirected_edge(0, 1, 1);

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
                        graph_list->add_undirected_edge(v1, v2, weight);
                        graph_matrix->add_undirected_edge(v1, v2, weight);
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

        cout << "[1] - Dijkstra, [2] - Bellman-Ford, [3] - Prim, [4] - Kruskal, [0] - wyjdz" << endl;
        int alg;
        cin >> alg;

        int v;
        float d;
        int number;
        double final_time_list = 0;
        double final_time_matrix = 0;


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

                case 1:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Dijkstra_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time_list += (double)time1.count();


                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Dijkstra_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time_matrix += (double)time2.count();

                    break;
                }

                case 2:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Bellman_Ford_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time_list += (double)time1.count();


                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Bellman_Ford_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time_matrix += (double)time2.count();

                    break;
                }

                case 3:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Prim_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time_list += (double)time1.count();


                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Prim_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time_matrix += (double)time2.count();

                    break;
                }

                case 4:{

                    //początek pomiaru
                    high_resolution_clock::time_point t1 = high_resolution_clock::now();

                    graph_list->Kruskal_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t2 = high_resolution_clock::now();
                    duration<double> time1 = duration_cast<duration<double>>(t2 - t1);
                    final_time_list += (double)time1.count();


                    //początek pomiaru
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();

                    graph_matrix->Kruskal_algorithm();

                    //koniec pomiaru
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
                    final_time_matrix += (double)time2.count();

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

        measurement << endl << "LISTA numer algorytmu: " << alg << " wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_list << endl << "średnia: " << setprecision(10) << final_time_list / number << endl;

        measurement << endl << "MACIERZ numer algorytmu: " << alg << " wierzcholki: " << v << "  gestosc: " << d << endl
                    << "  czas: " << fixed << setprecision(10) << final_time_matrix << endl << "średnia: " << setprecision(10) << final_time_matrix / number << endl << endl;

        measurement.close();
    }
}

