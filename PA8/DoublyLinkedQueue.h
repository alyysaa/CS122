#ifndef DOUBLYLINKEDQUEUE_H
#define DOUBLYLINKEDQUEUE_H


#include "DoublyLinkedList.h"

/// @brief A class that implements a doubly linked queue using a doubly linked list, int data only
class DoublyLinkedQueue: private DoublyLinkedList {
public:
    DoublyLinkedQueue();
    ~DoublyLinkedQueue();

    void enqueue(int);
    int dequeue();
    void clear();
    bool isEmpty();
    int size();

    
    void displayQueue(std::ostream &out = std::cout);
    void removeDivisibleBy(int, bool verbose = false, std::ostream &out = std::cout);
};

#endif