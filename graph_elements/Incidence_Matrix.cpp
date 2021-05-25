#include "Incidence_Matrix.h"
using namespace std;


Incidence_Matrix::Incidence_Matrix(int columns, int rows) {
    size_x = columns;
    size_y = rows;
    array = new int *[size_x];
    for (int i = 0; i < size_x; ++i) {
        array[i] = new int[size_y];
        for (int j = 0; j < size_y; ++j) {
            array[i][j] = 0;
        }
    }
}


Incidence_Matrix::~Incidence_Matrix() {
    for (int i = 0; i < size_x; ++i) {
        delete[] array[i];
    }
    delete[] array;
}


void Incidence_Matrix::add_column() {
    int **new_array = new int *[size_x + 1];
    for (int i = 0; i < size_x; ++i) {
        new_array[i] = new int[size_y];
        for (int j = 0; j < size_y; ++j) {
            new_array[i][j] = array[i][j];
        }
    }
    new_array[size_x] = new int[size_y];
    for (int j = 0; j < size_y; ++j) {
        new_array[size_x][j] = 0;
    }
    for (int i = 0; i < size_x; ++i) {
        delete[] array[i];
    }
    delete[] array;
    ++size_x;
    array = new_array;
}


void Incidence_Matrix::set_new_edge(int vertex, int value) {
    array[size_x - 1][vertex] = value;
}

int Incidence_Matrix::get(int x, int y) {
    return array[x][y];
}

void Incidence_Matrix::set(int x, int y, int value) {
    array[x][y] = value;
}

bool Incidence_Matrix::are_undirected_connected(int x, int y) {
    for (int i = 0; i < size_x; ++i) {
        if (array[i][x] != 0 && array[i][y] != 0) {
            return true;
        }
    }
    return false;
}

bool Incidence_Matrix::are_directed_connected(int x, int y) {
    for (int i = 0; i < size_x; ++i) {
        if (array[i][x] == 1 && array[i][y] == -1) {
            return true;
        }
    }
    return false;
}
