#ifndef SIEVE_H
#define SIEVE_H

#include "DoublyLinkedQueue.h"
#include <cmath>

/// @brief A class that implements the Sieve of Eratosthenes, using two DoublyLinked Queues
class Sieve {
private:
    DoublyLinkedQueue *numQueue;
    DoublyLinkedQueue *primeQueue;
    int n;
public:
    Sieve(int n = 0);
    ~Sieve();

    void computePrimes(int max, bool verbose = false, std::ostream &out = std::cout);
    void computePrimes() { computePrimes(n); }

    int reportResults(double &, std::ostream &out = std::cout);


};
#endif