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


void Adjacency_List::add_edge(int neighbour, int weight) {
    auto *new_element = new List_Element(neighbour, weight, tail, nullptr);

    if (tail == nullptr)
        head = new_element;   // dodanie elementu będącego ogonem i głową (gdy ogon wskazuje na NULL)
    else
        tail->next = new_element;
    tail = new_element;
}


void Adjacency_List::remove_vertex(List_Element *element) {
    --list_size;
    List_Element *left = element->prev;
    List_Element *right = element->next;
    delete element;

    if (left != nullptr)
        left->next = right;
    if (right != nullptr)
        right->prev = left;
}


List_Element *Adjacency_List::get_head() {
    return head;
}
