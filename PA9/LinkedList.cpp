#include "LinkedList.h"

/// @brief DVC
LinkedList::LinkedList() {
    head = NULL;
}

/// @brief constructs a linked list from an array of values
/// @param values values to be added to the linked list
/// @param size size of values
LinkedList::LinkedList(int values[], int size) {
    head = NULL;
    //get size of array
    for (int i = 0; i < size; i++) {
        appendNode(values[i]);
    }
}

/// @brief Destructor, deletes all nodes/frees memory
LinkedList::~LinkedList() {
    Node *nodePtr = head;
    while (nodePtr != NULL) {
        Node *tmp = nodePtr;
        nodePtr = nodePtr->next;
        delete tmp;
    }
}

/// @brief inserts a node at the front of the linked list
/// @param value to prepend
void LinkedList::insertAtFront(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

/// @brief displays the list in order from head to tail
void LinkedList::displayList() {
    Node *nodePtr = head;
    while (nodePtr != NULL) {
        std::cout << nodePtr->value << " ";
        nodePtr = nodePtr->next;
    }
    std::cout << std::endl;
}

/// @brief adds a node to the end of the linked list
/// @param value to append
void LinkedList::appendNode(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }
    else {
        Node *nodePtr = head;
        while (nodePtr->next != NULL) {
            nodePtr = nodePtr->next;
        }
        nodePtr->next = newNode;
    }
}

/// @brief public function to get max, calls helper
/// @return max value of linked list
int LinkedList::getMaxValue() {
    return head == NULL ? -1 : getMaxValueHelper(head, head->value);
}

/// @brief private recursive function to get max value
/// @param cur current node
/// @param max current max value
/// @return the maximum of cur->value and max, whichever is larger
int LinkedList::getMaxValueHelper(Node *cur, int max) {
    return cur == NULL ? max : getMaxValueHelper(cur->next, cur->value > max ? cur->value : max);
}

