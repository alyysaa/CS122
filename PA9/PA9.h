#ifndef PA9_H
#define PA9_H

#include<iostream>
#include<vector>
#include"LinkedList.h"

// for maze solving visualization, not required for PA9
#include<chrono>
#include<thread>

// unicode symbols for maze path display
#define LEFT_ARROW "\u2190"
#define UP_ARROW "\u2191"
#define RIGHT_ARROW "\u2192"
#define DOWN_ARROW "\u2193"
#define WALL "\u25A1"
#define TARGET "\u25CE"

int countDigits(std::string);
int sumDigits(int);
bool isPalindrome(std::string);
void generateSubstrings(std::string, std::vector<std::string> &);
void substringHelper(std::string, std::vector<std::string> &, int, int);

struct Coordinate {
    int row;
    int col;

    //extras, not required for PA9
    Coordinate(int r, int c): row(r), col(c) { }
    Coordinate(): row(0), col(0) { }
};


void displayMaze(char[8][8]);
void createRandomMaze(char[8][8]);


bool traverseMaze(char[8][8], Coordinate[], int *, bool verbose = false, int row = 0, int col = 0);

void runTask1();
void runTask2();
void runTask3();
void runTask4();
void runTask5();

void contCheck();
void runBONUSTask(bool verbose = false);
void runAllTasks(bool wait = true, bool bonusVerbose = false, bool onlyBonus = false);


#endif