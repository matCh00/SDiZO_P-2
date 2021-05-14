#include "list.h"
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

void List::push(int data, int weight)
{
    Node *p = new Node;
    p->data = data;
    p->weight = weight;
    if(head)
        p->next = head;
    else
        p->next = nullptr;
    head = p;
    size++;
}

void List::clear()
{
    Node *p = head;

    while (p)
    {
        Node *next = p->next;
        free(p);
        p = next;
    }
    size = 0;
    head = nullptr;
}

Node* List::get_head()
{
    return head;
}

List::List()
{
    head = nullptr;
    size = 0;
}

List::~List()
{
    clear();
}