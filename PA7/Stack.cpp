#include "Stack.h"

template <typename T>
Stack<T>::Stack() {
    LinkedList<T>();
}

template <typename T>
Stack<T>::~Stack(){
    //nothing needs to be done, superclass destructor will handle
}


template <typename T>
void Stack<T>::push(T value) {
    LinkedList<T>::prepend(value);
}

template <typename T>
T Stack<T>::pop() {
    return LinkedList<T>::removeFront();
}

template <typename T>
T Stack<T>::peek() {
    return LinkedList<T>::head->value;
}

template <typename T>
bool Stack<T>::isEmpty() {
    return LinkedList<T>::isEmpty();
}


