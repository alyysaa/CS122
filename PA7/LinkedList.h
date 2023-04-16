#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#include <cstdlib>
#include <stdexcept>

/// @brief Singly linked list class
/// @tparam T type of data to store in the list
template <typename T>
class LinkedList {
protected:

    /// @brief Node class, used to store data and a pointer to the next node
    struct Node {
        T value;
        struct Node *next;

        Node(T newVal, Node *nextPtr = NULL) {
            value = newVal;
            next = nextPtr;
        }
    };
    Node *head;
public:
    LinkedList() : head(NULL) {};
    ~LinkedList();
    void prepend(T); //equivalent to insertAtFront(T), as required by the assignment
    T removeFront(); //equivalent to deleteAtFront(), as required by the assignment
    bool isEmpty();

    //other methods that might be in a linked list, not required by assignment
    // void append(T);
    // T removeBack();
    // T removeAt(int);
    // void insertAt(T, int);
    // T get(int);
    // int size();
    // bool isEmpty();
    // std::string to_string();

};

#endif