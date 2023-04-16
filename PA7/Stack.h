#ifndef STACK_H
#define STACK_H

// both .h and .cpp are needed because of where the template implementations are
// .cpp includes the .h
#include "LinkedList.cpp"

/// @brief Simple stack class, implemented using a linked list
/// @tparam T data type to store in the stack
template <typename T>
class Stack : private LinkedList<T> {
public:
    Stack();
    ~Stack();
    void push(T);
    T pop();
    T peek();
    bool isEmpty();
};

#endif
