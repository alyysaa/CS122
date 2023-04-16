#ifndef STACK_H
#define STACK_H

// both .h and .cpp are needed because of where the template implementations are
// .cpp includes the .h
#include "LinkedList.cpp"

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
