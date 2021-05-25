#include "Graph_List.h"
#include "Graph_Matrix.h"
#include <fstream>
#include <iostream>
using namespace std;


void load_from_file(Graph_List *graph_list, Graph_Matrix *graph_matrix, bool directed) {
    cout << "Podaj nazwe pliku lub jego sciezke: ";
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

            if (directed) {
                graph_list->add_directed_edge(v1, v2, weight);
                graph_matrix->add_directed_edge(v1, v2, weight);
            }
            else {
                graph_list->add_undirected_edge(v1, v2, weight);
                graph_matrix->add_undirected_edge(v1, v2, weight);
            }

        }
    } else cout << "Wystapil problem podczas otwierania pliku\n";
    file.close();
}



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
    // losujemy krawędzie, gdzie nowa krawędź zaczyna się tam gdzie skończyła poprzednia
    // aby mieć cykl, żeby dało się dojść z każdego wierzchołka do każdego wierzchołka
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


    //losujemy krawędź, jeśli już taka krawędź istnieje to usuwamy ze zbioru możliwych krawędzi, jeśli nie to dodajemy do grafu
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






int main(){

    //Graph_Matrix *graphM = new Graph_Matrix(6);
/*
    graphM->add_directed_edge(0, 4, 3);
    graphM->add_directed_edge(0, 2, 2);
    graphM->add_directed_edge(4, 1, 3);
    graphM->add_directed_edge(2, 3, 1);
    graphM->add_directed_edge(3, 4, 5);
    graphM->add_directed_edge(4, 5, 9);
*/
    //graphM->print(); //ok

    // directed
    //graphM->Bellman_Ford_algorithm(); //ok
    //graphM->Dijkstra_algorithm();  // ok

    // undirected
    //graphM->Prim_algorithm();  // ok
    //graphM->Kruskal_algorithm(); //ok



    //Graph_List *graphL = new Graph_List(6);
/*
    graphL->add_directed_edge(0, 4, 3);
    graphL->add_directed_edge(0, 2, 2);
    graphL->add_directed_edge(4, 1, 3);
    graphL->add_directed_edge(2, 3, 1);
    graphL->add_directed_edge(3, 4, 5);
    graphL->add_directed_edge(4, 5, 9);
*/
    //graphL->print(); //ok

    // directed
    //graphL->Bellman_Ford_algorithm(); //ok
    //graphL->Dijkstra_algorithm();  // ok

    // undirected
    //graphL->Kruskal_algorithm(); //ok
    //graphL->Prim_algorithm();  // ok


    Graph_List *graphL = new Graph_List(5);
    Graph_Matrix *graphM = new Graph_Matrix(5);


    generate_edges(5, 30, graphL, graphM, true);
    //load_from_file(graphL, graphM, true);
    graphL->print();
    cout<<endl<<endl;
    graphM->print();


    return 0;
}



