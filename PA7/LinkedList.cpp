#include "LinkedList.h"

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}


template <typename T>
void LinkedList<T>::prepend(T value) {
    Node *newNode = new Node(value, head);
    head = newNode;
}

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

template <typename T>
bool LinkedList<T>::isEmpty() {
    return head == NULL;
}

