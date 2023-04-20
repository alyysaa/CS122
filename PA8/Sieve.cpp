#include "Sieve.h"

/// @brief Creates a new Sieve object, initializing the two queues
/// @param n starting N value, defaults to 0
Sieve::Sieve(int n) {
    this->n = n;
    numQueue = new DoublyLinkedQueue();
    primeQueue = new DoublyLinkedQueue();
}

/// @brief Destroys the Sieve object, deleting the two queues
Sieve::~Sieve() {
    delete numQueue;
    delete primeQueue;
}

/// @brief computes the primes up to a given number using the Sieve of Eratosthenes. fills primeQueue with primes, and numQueue with non-primes
/// @param max maximum number to sieve up to, inclusive
/// @param verbose prints out extra information about the sieve if true, defaults to false
/// @param out std::ostream to print to, defaults to std::cout
void Sieve::computePrimes(int max, bool verbose, std::ostream &out) {
    if (n == max) return;

    n = max;
    if (!numQueue->isEmpty()) numQueue->clear();
    if (!primeQueue->isEmpty()) primeQueue->clear();

    for (int i = 2; i <= max; i++) {
        if (verbose) out << "Enqueuing " << i << std::endl;
        numQueue->enqueue(i);
    }

    if (verbose) out << "Enqueued numbers up to " << max << std::endl;

    int prime;
    double sqrt = std::sqrt(max);
    do {
        if (numQueue->isEmpty()) {
            break;
        }
        prime = numQueue->dequeue();

        if (verbose) out << "Prime: " << prime << std::endl;

        primeQueue->enqueue(prime);
        numQueue->removeDivisibleBy(prime, verbose, out);

    } while ((double)prime < sqrt);

    if (verbose) out << "Finished sieving\n\n";

    while (!numQueue->isEmpty()) {
        primeQueue->enqueue(numQueue->dequeue());
    }
}

/// @brief reports results on the sieve, printing the primes and returning the number of primes
/// @param percent percaent of numbers that are prime
/// @param out std::ostream to print to, defaults to std::cout
/// @return nubmer of primes calculated by last call to computePrimes
int Sieve::reportResults(double &percent, std::ostream &out) {
    out << "Primes up to " << n << " are as follows:" << std::endl;
    primeQueue->displayQueue(out);
    double primes = (double)primeQueue->size();
    percent = primes / (double)n * 100.0;
    return primes;
}