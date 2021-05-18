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
    auto *newElement = new Vertex(neighbour, edgeWeight, tail, nullptr);

    if (tail == nullptr)
        head = newElement;   // dodanie elementu będącego ogonem i głową (gdy ogon wskazuje na NULL)
    else
        tail->next = newElement;
    tail = newElement;
}


bool Adjacency_List::remove_edge(int neighbour) {
    Vertex *temp = head;

    while (temp != nullptr) {
        if (temp->neighbour == neighbour) {
            remove_vertex(temp);
            return true;
        } else
            temp = temp->next;
    }
    return false;
}


void Adjacency_List::remove_vertex(Vertex *temp) {
    --list_size;
    Vertex *left = temp->prev;
    Vertex *right = temp->next;
    delete temp;

    if (left != nullptr)
        left->next = right;
    if (right != nullptr)
        right->prev = left;
}


Vertex *Adjacency_List::get_head() {
    return head;
}
