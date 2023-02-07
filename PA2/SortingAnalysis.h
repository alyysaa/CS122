#include <fstream>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

// File header for each of the output files
// is not used for compare file
static string FILE_HEADER = "Vector Configuration, Time, #Data Comparisons, #Loop Comparisons, #Data Assignments, #Loop Assignments, #Other Operations, #Total Operations";


// Function Prototypes

// returns a vector of size n with random integers
vector<int> generateRandomVector(int);

// returns a vector of size n with sorted integers
vector<int> generateSortedVector(int);

// returns a vector of size n with reverse sorted integers
vector<int> generateReverseVector(int);

// returns the count of sorting operations, the integer pointer is used to return additional statistics
int selectionSortCount(vector<int>, int *);

// returns the count of sorting operations, the integer pointer is used to return additional statistics
int bubbleSortCount(vector<int>, int *);

// returns the count of sorting operations, the integer pointer is used to return additional statistics
int insertionSortCount(vector<int>, int *);

// writes statistics of a specific sort to a file
void writeStats(ofstream &, int *, int, string);

// runs all sorts for a given vector and writes to files
void allSortsAndStats(vector<int>, string, ofstream &, ofstream &, ofstream &, ofstream &);

// runs all functions, only function called by main
void run();