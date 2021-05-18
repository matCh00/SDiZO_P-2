#pragma once
#include <iostream>

// klasa reprezentująca macierz incydencji
class Incidence_Matrix {

    int **array;   // wskaźnik na wskaźnik
    int size_x;     // liczba wierszy
    int size_y;     // liczba kolumn

public:

    Incidence_Matrix(int, int);  // konstruktor
    ~Incidence_Matrix();         // destruktor

    void add_column();             // dodanie kolumny
    void set_new_edge(int, int);   // ustawienie nowej krawędzi
    int get(int, int);          // popierz pozycję
    void set(int, int, int);    // ustaw pozycję
    bool are_undirected_connected(int, int);   // sprawdzanie połączenia
    bool are_directed_connected(int, int);     // sprawdzanie połączenia
    void print();
};



