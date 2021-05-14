#include "min_heap.h"
#include <iostream>
using namespace std;

void Min_Heap::push(int start, int end, int weight){

    Edge *temp = new Edge[size + 1];

    for (int i = 0; i < size; i++) {
        temp[i].start_vertex = array[i].start_vertex;
        temp[i].end_vertex = array[i].end_vertex;
        temp[i].weight = array[i].weight;
    }

    if (size == 0)
        delete array;
    else
        delete[] array;
    array = temp;

    int i = size;
    int j = (i - 1) / 2;
    while (i > 0 && array[j].weight > weight)
    {
        array[i].start_vertex = array[j].start_vertex;
        array[i].end_vertex = array[j].end_vertex;
        array[i].weight = array[j].weight;
        i = j;
        j = (i - 1) / 2;
    }
    array[i].weight = weight;
    array[i].end_vertex = start;
    array[i].start_vertex = end;
    size++;
}


void Min_Heap::pop()
{
    if (size == 1)
    {
        Edge *temp = new Edge;
        delete[] array;
        array = temp;
        size = 0;
    }
    else if(size > 1)
    {
        array[0].weight = array[size - 1].weight;
        array[0].start_vertex = array[size - 1].start_vertex;
        array[0].end_vertex = array[size - 1].end_vertex;

        Edge *temp = new Edge[size - 1];
        for (int i = 0; i < size - 1; i++)
        {
            temp[i].weight = array[i].weight;
            temp[i].start_vertex = array[i].start_vertex;
            temp[i].end_vertex = array[i].end_vertex;
        }
        delete[] array;
        array = temp;
        size--;
    }

    if (size - 1)
    {
        Edge e;
        e.weight = array[0].weight;
        e.end_vertex = array[0].end_vertex;
        e.start_vertex = array[0].start_vertex;
        int i = 0, j = 1;
        while (j < size)
        {
            if (j + 1 < size && array[j + 1].weight < array[j].weight)
                j++;
            if (e.weight <= array[j].weight)
                break;
            array[i].weight = array[j].weight;
            array[i].start_vertex = array[j].start_vertex;
            array[i].end_vertex = array[j].end_vertex;
            i = j;
            j = 2 * j + 1;
        }
        array[i].weight = e.weight;
        array[i].start_vertex = e.start_vertex;
        array[i].end_vertex = e.end_vertex;
    }
}


bool Min_Heap::is_empty()
{
    if (size == 0)
        return true;

    return false;
}

Edge Min_Heap::get_root()
{
    return array[0];
}

void Min_Heap::clear()
{
    if (size > 0)
    {
        delete[] array;
        array = nullptr;
        size = 0;
    }
    else
        return;
}

Min_Heap::Min_Heap()
{
}

Min_Heap::~Min_Heap()
{
    clear();
}
