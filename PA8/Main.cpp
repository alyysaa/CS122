#include "Sieve.h"
#include <fstream>

void SieveLoop(Sieve &s, bool verbose = false, std::ostream &out = std::cout) {
    std::cout << "This program computes all primes up to a maximum using the Sieve of Eratosthenes\n";
    while (true) {
        int n;
        std::cout << "Please enter a positive integer greater than 1 (-1 to quit): ";

        std::string input;
        std::getline(std::cin, input);
        try {
            n = std::stoi(input);
        }
        //if catch invalid arg or out of range
        catch (std::invalid_argument) {
            n = -2;
        }
        catch (std::out_of_range) {
            n = -2;
        }

        if (n < 2) {
            if (n == -1) {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            std::cout << "Invalid input. Try again.\n\n";
            continue;
        }
        if (n >= 100000) { //warning for large numbers > 100,000
            std::cout << "This program is not designed to handle numbers this large. If you would like to continue, please enter 'y': ";
            std::string input;
            std::getline(std::cin, input);
            if (std::tolower(input[0]) != 'y') {
                continue;
            }
        }

        s.computePrimes(n, verbose, out);
        double percent;
        std::cout << s.reportResults(percent) << " / " << n << " = "
            << percent << "% primes\n\n";
    }
}


int main(int argc, char *argv[]) {


    Sieve s;

    //tests for computePrimes and reportResults, uncomment to run
    //.out.txt files are cleaned with my makefile (make tclean), feel free to change the name
    // std::string filename = "SieveOutput.out.txt";
    // std::ofstream out = std::ofstream(filename);
    // for (int i = 2; i < 100; i++) {
    //     s.computePrimes(i, false, out);
    //     double percent;
    //     int primes = s.reportResults(percent, out);
    //     out << primes << " / " << i << " = " << percent << "% primes\n\n";
    // }
    // out.close();

    //tests for extra credit functions, uncomment to run
    // DoublyLinkedList ll;
    // ll.addToFront(1);
    // for (int i = 2; i < 10; i++) {
    //     ll.insertInOrder(i);
    // }
    // ll.displayList();
    // for (int i = 0; i < 9; i++) {
    //     std::cout << ll.deleteAtEnd() << std::endl;
    // }

    //infinite user input as described in the assignment, -1 to exit the program
    SieveLoop(s, argc > 1 ? argv[1][0] == 'v' : false);

    return 0;
}