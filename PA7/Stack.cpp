#include "Stack.h"

/// @brief Just calls the superclass constructor
/// @tparam T
template <typename T>
Stack<T>::Stack() {
    LinkedList<T>();
}

/// @brief nothing needs to be done, superclass destructor will handle it
/// @tparam T
template <typename T>
Stack<T>::~Stack(){
}

/// @brief pushes value to stack
/// @tparam T type
/// @param value value to push
template <typename T>
void Stack<T>::push(T value) {
    LinkedList<T>::prepend(value);
}


/// @brief return value at top of stack, remove value from stack
template <typename T>
T Stack<T>::pop() {
    return LinkedList<T>::removeFront();
}

/// @return value at top of stack
template <typename T>
T Stack<T>::peek() {
    return LinkedList<T>::head->value;
}

/// @return true if stack is empty, false otherwise
template <typename T>
bool Stack<T>::isEmpty() {
    return LinkedList<T>::isEmpty();
}


