#include "SortingAnalysis.h"

// number of data comparisons for each sort

// input: v - a vector of integers
//        size - the size of the vector
// output: none
// description: fills v with size random integers
vector<int> generateRandomVector(int size)
{
  vector<int> v;
  for (int i = 0; i < size; i++)
  {
    v.push_back(rand() % (size * 2)); // doubled just to add less chance of duplicates
                                      // algorithms can handle them, but they're not fun
  }
  return v;
}

// input: v - a vector of integers
//        size - the size of the vector
// output: none
// description: fills v with size integers, sorted in ascending order
vector<int> generateSortedVector(int size)
{
  vector<int> v;
  for (int i = 0; i < size; i++)
  {
    v.push_back(i);
  }
  return v;
}

// input: v - a vector of integers
//        size - the size of the vector
// output: none
// description: fills v with size integers, sorted in descending order
vector<int> generateReverseVector(int size)
{
  vector<int> v;
  for (int i = size; i > 0; i--)
  {
    v.push_back(i);
  }
  return v;
}

// input: v - a vector of integers
// output: total number of operations
// description: sorts v using selection sort, and returns an array of statistics about the sort
// postcondition: stats is an array of 7 integers, containing:
//         [0] - time of sort (in milliseconds)
//         [1] - number of data comparisons
//         [2] - number of loop comparisons
//         [3] - number of data assignments
//         [4] - number of loop assignments
//         [5] - number of other operations
//         [6] - number of total operations
int selectionSortCount(vector<int> v, int *stats)
{
  int datComp = 0;                                                               // number of data comparisons
  int loopComp = 0;                                                              // number of loop comparisons
  int datAssign = 0;                                                             // number of data assignments
  int loopControl = 0;                                                           // number of loop control changes
  int otherOp = 0;                                                               // number of other operations
  chrono::steady_clock::time_point start = chrono::high_resolution_clock::now(); // start timer

  otherOp += 2; // memory alloction in other
  int minIndex, minValue;

  loopControl++; // size
  int size = v.size();

  loopControl++; // start = 0
  for (int start = 0; start < size - 1; start++, loopControl++)
  {
    loopComp++; // start < size - 1 true

    minIndex = start;
    minValue = v[start];
    datAssign += 2; // above two

    loopControl++; // index = start + 1
    for (int index = start + 1; index < size; index++, loopControl++)
    {
      loopComp++; // index < size true

      datComp++; // v[index] < minValue
      if (v[index] < minValue)
      {
        minIndex = index;
        minValue = v[index];
        datAssign += 2; // above two
      }
    }
    loopComp++; // index < size false
    v[minIndex] = v[start];
    v[start] = minValue;
    datAssign += 2; // above two
  }
  chrono::steady_clock::time_point end = chrono::high_resolution_clock::now(); // end timer
  loopComp++;                                                                  // start < size - 1 false

  // calculate duration, convert to milliseconds, and store in stats[0]
  stats[0] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  stats[1] = datComp;
  stats[2] = loopComp;
  stats[3] = datAssign;
  stats[4] = loopControl;
  stats[5] = otherOp;
  stats[6] = datComp + loopComp + datAssign + loopControl + otherOp;
  return stats[6];
}

// input: v - a vector of integers
// output: total number of operations
// description: sorts v using bubble sort, and returns an array of statistics about the sort
// postcondition: stats is an array of 7 integers, containing:
//         [0] - time of sort (in milliseconds)
//         [1] - number of data comparisons
//         [2] - number of loop comparisons
//         [3] - number of data assignments
//         [4] - number of loop assignments
//         [5] - number of other operations
//         [6] - number of total operations
int bubbleSortCount(vector<int> v, int *stats)
{
  int datComp = 0;                                                               // number of data comparisons
  int loopComp = 0;                                                              // number of loop comparisons
  int datAssign = 0;                                                             // number of data assignments
  int loopControl = 0;                                                           // number of loop control changes
  int otherOp = 0;                                                               // number of other operations
  chrono::steady_clock::time_point start = chrono::high_resolution_clock::now(); // start timer

  int temp;
  bool swap;
  otherOp += 2; // memory allocation in other

  loopControl++;
  int size = v.size();

  do
  {
    loopControl++;
    swap = false;

    loopControl++;
    for (int i = 0; i < size - 1; i++, loopControl++)
    {
      loopComp++; // i < size - 1 true

      datComp++; // v[i] > v[i + 1]
      if (v[i] > v[i + 1])
      {
        temp = v[i];
        otherOp++; // temp storage in other

        v[i] = v[i + 1];
        v[i + 1] = temp;
        datAssign += 2; // swap takes two

        loopControl++; // exit = true
        swap = true;
      }
    }
    loopComp++; // i < size - 1 false
    loopComp++; // exit evaluation
  } while (swap);
  chrono::steady_clock::time_point end = chrono::high_resolution_clock::now(); // end timer

  // calculate duration, convert to milliseconds, and store in stats[0]
  stats[0] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  stats[1] = datComp;
  stats[2] = loopComp;
  stats[3] = datAssign;
  stats[4] = loopControl;
  stats[5] = otherOp;
  stats[6] = datComp + loopComp + datAssign + loopControl + otherOp;
  return stats[6];
}

// input: v - a vector of integers
// output: total number of operations
// description: sorts v using insertion sort, and returns an array of statistics about the sort
// postcondition: stats is an array of 7 integers, containing:
//         [0] - time of sort (in milliseconds)
//         [1] - number of data comparisons
//         [2] - number of loop comparisons
//         [3] - number of data assignments
//         [4] - number of loop assignments
//         [5] - number of other operations
//         [6] - number of total operations
int insertionSortCount(vector<int> v, int *stats)
{
  int datComp = 0;                                                               // number of data comparisons
  int loopComp = 0;                                                              // number of loop comparisons
  int datAssign = 0;                                                             // number of data assignments
  int loopControl = 0;                                                           // number of loop control changes
  int otherOp = 0;                                                               // number of other operations
  chrono::steady_clock::time_point start = chrono::high_resolution_clock::now(); // start timer

  int nextIndex, nextValue;
  otherOp += 2; // memory allocation in other

  loopControl++;
  int size = v.size();

  loopControl++;
  for (int nextIndex = 1; nextIndex < size; nextIndex++, loopControl++)
  {
    loopComp++; // nextIndex < size true

    nextValue = v[nextIndex];
    otherOp++; // nextValue storage in other

    int moveIndex = nextIndex;
    loopControl++; // moveIndex = nextIndex
    while (moveIndex > 0 && v[moveIndex - 1] > nextValue)
    {
      loopComp++; // loop condition true

      v[moveIndex] = v[moveIndex - 1];
      datAssign++; // above

      moveIndex--;
      loopControl++; // moveIndex--
    }
    loopComp++; // loop condition false

    v[moveIndex] = nextValue;
    datAssign++; // above
  }
  loopComp++;                                                                  // nextIndex < size false
  chrono::steady_clock::time_point end = chrono::high_resolution_clock::now(); // end timer

  // calculate duration, convert to microseconds, and store in stats[0]
  stats[0] = chrono::duration_cast<chrono::microseconds>(end - start).count();
  stats[1] = datComp;
  stats[2] = loopComp;
  stats[3] = datAssign;
  stats[4] = loopControl;
  stats[5] = otherOp;
  stats[6] = datComp + loopComp + datAssign + loopControl + otherOp;
  return stats[6];
}

// input: file - an ofstream of the file to be written to
//        stats - an array of 7 integers, containing data about a sorted vector
//        size - the size of the sorted vector
//        genType - the type of vector that was sorted
// output: none
// description: writes the contents of stats to file, with the size of the vector sorted in csv format
void writeStats(ofstream &file, int *stats, int size, string genType)
{
  file << genType << " N=" << size << "," << stats[0] << "," << stats[1] << "," << stats[2] << "," << stats[3] << "," << stats[4] << "," << stats[5] << "," << stats[6] << endl;
}

// input: v - a vector of integers
//        genType - the method of generation for the vector
//        compareFile - an ofstream of the file to be written to
//        selectionFile - an ofstream of the file to be written to for selection sort
//        bubbleFile - an ofstream of the file to be written to for bubble sort
//        insertionFile - an ofstream of the file to be written to for insertion sort
// output: none
// descrption: handles sorting v in all the methods defined by this program, writes stats for each sort to its own file
//             and compares the generation methods in another file
void allSortsAndStats(vector<int> v, string genType, ofstream &compareFile, 
        ofstream &selectionFile, ofstream &bubbleFile, ofstream &insertionFile)
{
  int stats[7];
  int size = v.size();
  
  int selectionOps = selectionSortCount(v, stats);
  int selectionTime = stats[0];
  writeStats(selectionFile, stats, size, genType);

  int bubbleOps = bubbleSortCount(v, stats);
  int bubbleTime = stats[0];
  writeStats(bubbleFile, stats, size, genType);

  int insertionOps = insertionSortCount(v, stats);
  int insertionTime = stats[0];
  writeStats(insertionFile, stats, size, genType);

  compareFile << genType << " N=" << size << "," << "Operations" << "," 
              << selectionOps << "," << bubbleOps << "," << insertionOps << endl;

  compareFile << genType << " N=" << size << "," << "Time" << "," 
              << selectionTime << "," << bubbleTime << "," << insertionTime << endl;


  
}

// input: none
// output: none
// description: generates a random vector of integers, and sorts it using selection, bubble, and insertion sort
void run()
{

  ofstream selectionFile("selection.csv");
  ofstream bubbleFile("bubble.csv");
  ofstream insertionFile("insertion.csv");
  ofstream compareFile("compare.csv");

  selectionFile << FILE_HEADER << endl;
  bubbleFile << FILE_HEADER << endl;
  insertionFile << FILE_HEADER << endl;

  compareFile << "Generation Method, "<< "Measurement, " << "Selection Sort, " << "Bubble Sort, " << "Insertion Sort" << endl;


  srand(time(NULL));

  int stats[7];
  vector<int> v;

  allSortsAndStats(generateSortedVector(500), "Sorted", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateSortedVector(1000), "Sorted", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateSortedVector(5000), "Sorted", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateSortedVector(10000), "Sorted", compareFile, selectionFile, bubbleFile, insertionFile);

  allSortsAndStats(generateReverseVector(500), "Reverse", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateReverseVector(1000), "Reverse", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateReverseVector(5000), "Reverse", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateReverseVector(10000), "Reverse", compareFile, selectionFile, bubbleFile, insertionFile);

  allSortsAndStats(generateRandomVector(500), "Random", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateRandomVector(1000), "Random", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateRandomVector(5000), "Random", compareFile, selectionFile, bubbleFile, insertionFile);
  allSortsAndStats(generateRandomVector(10000), "Random", compareFile, selectionFile, bubbleFile, insertionFile);
  
  
  selectionFile.close();
  bubbleFile.close();
  insertionFile.close();
}
