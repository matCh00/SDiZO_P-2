#include "Min_Heap.h"
using namespace std;

Min_Heap::Min_Heap() {

    size = 0;
    heap = new int[size];
}

Min_Heap::~Min_Heap() {

    delete[] heap;
    size = 0;
}

int Min_Heap::getParent(int index) {

    return (index - 1) / 2;
}

int Min_Heap::getLeftChild(int index) {

    return (2 * index + 1);
}

int Min_Heap::getRightChild(int index) {

    return (2 * index + 2);
}

void Min_Heap::relocate(int newSize) {

    int* temp = new int[newSize];
    if (newSize >= size) {

        for (int i = 0; i < size; i++) {

            temp[i] = heap[i];
        }
    }
    else
    {
        for (int i = 0; i < newSize; i++) {

            temp[i] = heap[i];
        }
    }
    delete heap;
    heap = temp;
}

void Min_Heap::swap(int *x, int *y) {

    int temp = *x;
    *x = *y;
    *y = temp;
}

void Min_Heap::push(int key) {

    relocate(size + 1);
    size++;
    int i = size - 1;
    heap[i] = key;

    while (i != 0 && heap[getParent(i)] > heap[i])
    {
        swap(&heap[i], &heap[getParent(i)]);
        i = getParent(i);
    }
}

void Min_Heap::decreaseKey(int index, int newValue) {

    heap[index] = newValue;
    while (index != 0 && heap[getParent(index)] > heap[index])
    {
        swap(&heap[index], &heap[getParent(index)]);
        index = getParent(index);
    }
}

int Min_Heap::pop() {

    if (size <= 0) {

        return 0;
    }
    else if (size == 1) {

        size--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[size - 1];
    relocate(size - 1);
    size--;
    heapify(0);

    return root;
}

void Min_Heap::remove(int value) {

    int key = find(value);
    if (key == -1) {

        std::cout << "Could not remove value: " << value << std::endl;
        return;
    }

    decreaseKey(key, INT_MIN);
    pop();
}

void Min_Heap::heapify(int index) {

    int leftChild = getLeftChild(index);
    int rightChild = getRightChild(index);
    int smallest = index;

    if (leftChild < size && heap[leftChild] < heap[smallest])
        smallest = leftChild;
    if (rightChild < size && heap[rightChild] < heap[smallest])
        smallest = rightChild;
    if (smallest != index) {

        swap(&heap[index], &heap[smallest]);
        heapify(smallest);
    }
}

bool Min_Heap::find(int value) {

    for (int i = 0; i < size; i++) {

        if (heap[i] == value)
            return true;
    }

    return false;
}

void Min_Heap::display() {

    for (int i = 0, lvl = 1; i < size; i++) {

        if (i + 1 == lvl) {

            lvl *= 2;
            cout << endl;
        }

        cout << heap[i] << " ";
    }

    cout << endl;
}

void Min_Heap::display(int index, int offset) {

    if (getRightChild(index) < size)
        display(getRightChild(index), offset + 5);
    cout << setw(offset) << heap[index] << std::endl;
    if (getLeftChild(index) < size)
        display(getLeftChild(index), offset + 5);
}

void Min_Heap::displayTree() {

    if (size != 0)
        display(0, 0);
}

int Min_Heap::getSize() {

    return size;
}