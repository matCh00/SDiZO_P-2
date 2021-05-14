#pragma once


struct Edge {

    int start_vertex;
    int end_vertex;
    int weight;
};


class Min_Heap {

    int size;
    Edge *array;

public:
    void push(int, int, int);
    void pop();
    bool is_empty();
    void clear();

    Edge get_root();
    Min_Heap();
    ~Min_Heap();
};



