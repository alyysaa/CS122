#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

/// @brief Linked List class, int values, not sorted
class LinkedList{
    private:
    struct Node{
        int value;
        struct Node *next;
    };
    Node *head;

    int getMaxValueHelper(Node *, int);

    public:

    LinkedList();
    LinkedList(int[], int);
    ~LinkedList();
    void insertAtFront(int);
    void displayList();
    void appendNode(int);

    //public pa9 function
    int getMaxValue();
};

#endif
