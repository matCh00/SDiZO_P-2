#pragma once
#include <iostream>

// klasa reprezentująca macierz incydencji
// użycie: Graph_Matrix

class Incidence_Matrix {

    int **array;    // wskaźnik na wskaźnik
    int size_x;     // liczba wierszy
    int size_y;     // liczba kolumn

public:

    Incidence_Matrix(int, int);  // konstruktor
    ~Incidence_Matrix();         // destruktor

    void add_column();             // dodanie kolumny
    void set_new_edge(int, int);   // ustawienie nowej krawędzi
    int get(int, int);             // pobieranie pozycji
    void set(int, int, int);       // ustawienie pozycji
    bool are_undirected_connected(int, int);   // sprawdzanie połączenia
    bool are_directed_connected(int, int);     // sprawdzanie połączenia
    void print();                              // wypisanie grafu
};



