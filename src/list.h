#pragma once


struct Node {

    Node *next;
    int data;
    int weight;
};


class List {

    int size;
    Node *head;

public:
    void push(int, int);
    void clear();

    Node *get_head();
    List();
    ~List();
};



