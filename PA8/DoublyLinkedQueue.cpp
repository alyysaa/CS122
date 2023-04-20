#include "DoublyLinkedQueue.h"

/// @brief creates a new DoublyLinkedQueue object, handled by base class
DoublyLinkedQueue::DoublyLinkedQueue() {
    // Nothing to do here
}

/// @brief destroys the queue, handled by base class
DoublyLinkedQueue::~DoublyLinkedQueue() {
    // Nothing to do here
}

/// @brief adds data to the end of the queue, mostly handled by base class
/// @param data data to add
void DoublyLinkedQueue::enqueue(int data) {
    this->addToEnd(data);
}

/// @brief removes data from the front of the queue, mostly handled by base class
/// @return data at front of queue, or -1 if not found/queue empty
int DoublyLinkedQueue::dequeue() {
    return this->deleteAtFront();
}

/// @brief clears the queue, mostly handled by base class
void DoublyLinkedQueue::clear() {
    this->destroyList();
}

/// @return true if the queue is empty, false otherwise
bool DoublyLinkedQueue::isEmpty() {
    return this->head == nullptr;
}

/// @return size of the queue
int DoublyLinkedQueue::size() {
    return this->listSize;
}

/// @brief displays the queue to the given output stream
/// @param out std::ostream& the output stream to display the queue to, defaults to std::cout
void DoublyLinkedQueue::displayQueue(std::ostream &out) {
    this->displayList(out);
}

/// @brief removes all nodes from the queue that are divisible by the given number
/// @param div int the number to divide by
/// @param verbose bool whether or not to print the deleted nodes to the given output stream
/// @param out std::ostream& the output stream to print the deleted nodes to, defaults to std::cout
void DoublyLinkedQueue::removeDivisibleBy(int div, bool verbose, std::ostream &out) {
    Node *current = this->head;

    while (current != nullptr) {
        if (current->data % div == 0) {
            if (verbose) out << "Deleting " << current->data << std::endl;

            int dData = current->data;
            current = current->next;
            this->deleteNode(dData);
        }
        else current = current->next;
    }
}
