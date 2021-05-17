#pragma once

/*
                         weight
        vertex  ------------------------->  next

 */

class Node {
public:
    Node *next;
    int vertex;
    int weight;

    Node();

    ~Node();
};
