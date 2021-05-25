#include "Adjacency_List.h"


Adjacency_List::Adjacency_List() {
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}


Adjacency_List::~Adjacency_List() {
    while (list_size) {
        remove_vertex(head);  // zwalnianie pamięci
    }
}


void Adjacency_List::add_edge(int neighbour, int edgeWeight) {
    auto *newElement = new List_Element(neighbour, edgeWeight, tail, nullptr);

    if (tail == nullptr)
        head = newElement;   // dodanie elementu będącego ogonem i głową (gdy ogon wskazuje na NULL)
    else
        tail->next = newElement;
    tail = newElement;
}


void Adjacency_List::remove_vertex(List_Element *temp) {
    --list_size;
    List_Element *left = temp->prev;
    List_Element *right = temp->next;
    delete temp;

    if (left != nullptr)
        left->next = right;
    if (right != nullptr)
        right->prev = left;
}


List_Element *Adjacency_List::get_head() {
    return head;
}
