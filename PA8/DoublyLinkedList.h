#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

/// @brief A class that implements a doubly linked list, int data only
class DoublyLinkedList {
protected:
    struct Node {
        int data;
        Node *next;
        Node *prev;
        Node(int data = 0, Node *next = nullptr, Node *prev = nullptr): data(data), next(next), prev(prev) { }
    };
    Node *head;
    Node *tail;
    int listSize;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void displayList(std::ostream &out = std::cout);
    void destroyList();
    void addToEnd(int);
    int deleteAtFront();
    int deleteNode(int);

    // Extra credit functions`
    void addToFront(int);
    int deleteAtEnd();
    void insertInOrder(int);
    
};

#endif