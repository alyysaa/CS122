#include "DoublyLinkedList.h"

/// @brief creates a new DoublyLinkedList object, sets pointers to nullptr and listSize to 0
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

/// @brief destroys the list, calls destroyList()
DoublyLinkedList::~DoublyLinkedList() {
    this->destroyList();
}

/// @brief displays the list to the given output stream
/// @param out std::ostream& the output stream to display the list to, defaults to std::cout
void DoublyLinkedList::displayList(std::ostream &out) {
    Node *current = head;
    while (current != nullptr) {
        out << current->data << " ";
        current = current->next;
    }
    out << std::endl;
}

/// @brief destroys the list, deallocates memory
void DoublyLinkedList::destroyList() {
    Node *current = head;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

/// @brief adds the given data to the end of the list
/// @param data data to add
void DoublyLinkedList::addToEnd(int data) {
    Node *newNode = new Node(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

/// @brief deletes the node at the front of the list, returns its data
/// @return data of the node at the front of the list, -1 if the list is empty or if the node is not found
int DoublyLinkedList::deleteAtFront() {
    if (head == nullptr) {
        return -1;
    }
    Node *temp = head;
    int data = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
    listSize--;
    return data;
}

/// @brief deletes the first found node with the given data
/// @param data data to delete
/// @return value removed, or -1 if not found or list is empty
int DoublyLinkedList::deleteNode(int data) {
    if (head == nullptr) {
        return -1;
    }
    Node *current = head;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }
    if (current == nullptr) {
        return -1;
    }
    if (current == head) {
        return this->deleteAtFront();
    }
    current->prev->next = current->next;
    if (current == tail) {
        tail = current->prev;
    } else {
        current->next->prev = current->prev;
    }
    int nData = current->data;
    delete current;
    listSize--;
    return nData;
}
