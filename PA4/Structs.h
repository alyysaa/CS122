#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const int NUM_LETTERS = 52;

/// @brief struct to store the count and frequency of a letter
/// @param count number of times a letter occurs in a string
/// @param frequency frequency of a letter in a string
struct LetterOccurrence
{
    int count;
    double frequency;
};

/// @brief struct to store the id, weight, width, length, and height of a package
/// @param id id of a package
/// @param weight weight of a package
/// @param width width of a package
/// @param length length of a package
struct Package
{
    int id;
    double weight;
    int width;
    int length;
    int height;
};

/// @brief task 1 driver, prompts user for strings and outputs a histogram of the letter occurences
void histogramInputLoop();

/// @brief outputs a histogram of the letter occurences in s
/// @param s string to output a histogram of
void occuranceHistogram(string s);

/// @brief clears letterOccs and computes the count and frequency of each letter in s
/// @param s string to process
/// @param letterOccs array of @code{LetterOccurrence} structs to be cleared and filled
void processString(const string s, LetterOccurrence letterOccs[]);

/// @brief computes the frequency of each letter in letterOccs to compute max from
/// @param letterOccs array of @code{LetterOccurrence} structs
void computeFrequencies(LetterOccurrence letterOccs[]);

/// @brief computes the maximum occurence of a letter in letterOccs, stores letter, count and frequency in c, count, and freq
/// @param letterOccs array of LetterOccurrence structs
/// @param c pointer to char to store the letter with the maximum occurence
/// @param count pointer to int to store the count of the letter with the maximum occurence
/// @param freq pointer to double to store the frequency of the letter with the maximum occurence
void computeMaximumOccurences(const LetterOccurrence letterOccs[], char* c, int* count, double* freq);

/// @brief outputs a histogram of the letter occurences in letterOccs
/// @param letterOccs array of LetterOccurrence structs, to be output
/// @param s string used to compute letterOccs
/// @param maxC char with the maximum occurence
/// @param maxCount count of the letter with the maximum occurence
/// @param maxFreq frequency of the letter with the maximum occurence
void outputHistogram(const LetterOccurrence letterOccs[], const string s, const char maxC, const int maxCount, const double maxFreq);

/////////////////////////// TASK TWO FUNCTIONS

/// @brief task 2 driver, takes filename from command line and outputs package stats, calling below functions as needed
/// @param fileName filename to read package data from
void takePackageInventory(string fileName);

/// @brief loads packages from inFile, stores driver name in driverName, stores number of packages in numPackages
/// @param inFile file to read package data from
/// @param driverName name of driver
/// @param numPackages number of packages
/// @return array of Package structs
Package* loadPackages(ifstream& inFile, string* driverName, int* numPackages);

/// @brief computes statistics for packages, stores in parameters
/// @param packages array of Package structs to be read from
/// @param numPackages number of packages (packages.size())
/// @param heaviestId id of heaviest package (filled in function)
/// @param heaviestWeight weight of heaviest package (filled in function)
/// @param avgWeight average weight of packages (filled in function)
void computePackageStats(const Package* packages, const int numPackages, int* heaviestId, double* heaviestWeight, double* avgWeight);


void computeLongestLen(const Package* packages, const int numPackages, int* longestLen);

/// @brief prints package inventory in a table format to console, including driver name, number of packages, heaviest package, and average weight
/// @param packages array of Package structs to print
/// @param numPackages numer of packages (packages.size())
/// @param maxLen the minimum number of characters to represent the longest package field (for table formatting)
/// @param driverName name of driver
/// @param heaviestId id of heaviest package
/// @param heaviestWeight weight of heaviest package
/// @param avgWeight average weight of all packages
void printPackageInventory(const Package* packages, const int numPackages, const int maxLen, const string driverName, const int heaviestId, const double heaviestWeight, const double avgWeight);

/// @brief identitcal to printPackageInventory, but recursive
/// @param packages array of Package structs to print
/// @param numPackages numer of packages (packages.size())
/// @param maxLen the minimum number of characters to represent the longest package field (for table formatting)
/// @param driverName name of driver
/// @param heaviestId id of heaviest package
/// @param heaviestWeight weight of heaviest package
/// @param avgWeight average weight of all packages
/// @param i index of next package to print
void recursivePrint(const Package* packages, const int numPackages, const int maxLen, const string driverName, const int heaviestId, const double heaviestWeight, const double avgWeight, int i);

#endif