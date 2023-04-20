#include "Sieve.h"
#include <fstream>

void SieveLoop(Sieve &s, bool vebose = false, std::ostream &out = std::cout) {
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
        s.computePrimes(n, vebose, out);
        double percent;
        std::cout << s.reportResults(percent) << " / " << n << " = "
            << percent << "% primes\n\n";
    }
}


int main(int argc, char *argv[]) {


    Sieve s;

    //.out.txt files are cleaned with my makefile (make tclean), feel free to change the name
    std::string filename = "SieveOutput.out.txt";
    std::ofstream out = std::ofstream(filename);

    for (int i = 2; i < 100; i++) {
        s.computePrimes(i, false, out);
        double percent;
        int primes = s.reportResults(percent, out);
        out << primes << " / " << i << " = " << percent << "% primes\n\n";
    }

    SieveLoop(s, argc > 1 ? argv[1][0] == 'v' : false);

    return 0;
}