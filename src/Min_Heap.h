#pragma once
#include <iostream>
#include <iomanip>

class Min_Heap {

    int *heap;
    int capacity;
    int size;

    int getParent(int);
    int getLeftChild(int);
    int getRightChild(int);
    void relocate(int);
    void swap(int*, int*);
    void heapify(int);
    void decreaseKey(int, int);
    void display(int, int);

public:
    Min_Heap();
    ~Min_Heap();

    int getSize();
    int pop();
    void push(int);
    void remove(int);
    bool find(int);
    void display();
    void displayTree();
};
