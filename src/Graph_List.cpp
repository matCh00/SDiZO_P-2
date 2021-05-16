#include "Graph_List.h"
using namespace std;


/*-----------------------------LISTA SĄSIEDZTWA-----------------------------

        ----------
       |          |           ------                  ------
       |   V1  <--|------->  |  V4  |  <---------->  |  V3  |  <---------->   ...
       |          |           ------                  ------
       |          |
       |          |           ------                  ------
       |   V2  <--|------->  |  V5  |  <---------->  |  V8  |  <---------->   ...
       |          |           ------                  ------
       |          |
       |          |           ------                  ------
       |   V3  <--|------->  |  V6  |  <---------->  |  V1  |  <---------->   ...
       |          |           ------                  ------
       |          |
        ----------

            ^
            |
   to jest tablica wskaźników na tablice


*/


// tworzenie (pustego) grafu - reprezentacja listowa (dzidziczenie po obiekcie Graph)
Graph_List::Graph_List(int size, bool directed) : Graph(size, directed) {

    // każdy element ma wartość NULL
    for (int i = 0; i < size; i++)
        adjacency_list.push_back(nullptr);
}


// usuwanie grafu
Graph_List::~Graph_List() {

    // usuwanie wszystkich elementów
    for (int i = 0; i < vertex_array.size(); i++)
        adjacency_list.pop_back();
}