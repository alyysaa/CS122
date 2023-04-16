#include "LinkedList.h"

/// @brief Desructor, deletes all nodes in the list
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

/// @brief inserts value at the front of the list
/// @tparam T type
/// @param value value to insert
template <typename T>
void LinkedList<T>::prepend(T value) {
    Node *newNode = new Node(value, head);
    head = newNode;
}

/// @brief return value at front of list, remove value from list
template <typename T>
T LinkedList<T>::removeFront() {
    if (head == NULL) {
        throw std::underflow_error("Cannot remove from empty list ");
    }
    Node *temp = head;
    head = head->next;
    T value = temp->value;
    delete temp;
    return value;
}

/// @return true if list is empty, false otherwise
template <typename T>
bool LinkedList<T>::isEmpty() {
    return head == NULL;
}

