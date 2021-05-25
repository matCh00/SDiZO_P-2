#pragma once
#include <iostream>

// klasa reprezentująca macierz incydencji
// użycie: Graph_Matrix

class Incidence_Matrix {

public:  // zmienne potrzebne do wypisania macierzy incydencji w klasie Graph_Matrix

    int **array;    // lista dwuwymiarowa
    int size_x;     // liczba wierszy
    int size_y;     // liczba kolumn

//public:

    Incidence_Matrix(int columns, int rows);  // konstruktor
    ~Incidence_Matrix();                      // destruktor

    void add_column();                             // dodanie kolumny
    void set_new_edge(int vertex, int value);      // ustawienie nowej krawędzi
    int get(int x, int y);                         // pobieranie pozycji
    void set(int x, int y, int value);             // ustawienie pozycji
    bool are_undirected_connected(int x, int y);   // sprawdzanie połączenia
    bool are_directed_connected(int x, int y);     // sprawdzanie połączenia
};



