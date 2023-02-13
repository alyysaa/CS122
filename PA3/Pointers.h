#include <iostream>
#include <fstream>

using namespace std;

//runs task 1, calling answerIntegerQuestions
void task1(string numbersFile);

//calls the other functions to answer the questions
void answerIntegerQuestions(const int num, bool *isMultiple, bool *isSumEven, bool *isPrime);

//returns true if num is a multiple of 7, 11, or 13, false otherwise
bool answerMultiple(const int num);

//returns true if the sum of the digits of num is even, false otherwise
bool answerSumEven(const int num);

//returns true if num is prime, false otherwise
bool answerPrime(const int num);

//runs task 2, calling findWinningLotteryTicket
void task2();

//returns true if the winning ticket is in the player's numbers, false otherwise
bool findWinningLotteryTicket(const int winningTicketNum, const int *playerNumbers, const int numPlayerNumbers);

//runs task 3, calling createWordsArray, sortWords, printWordsArr, and generateSentence
void task3(string wordsFile);

//creates an array of words from the file
string *createWordsArray(ifstream &inFile, const int size);

//sorts the array of words in alphabetical order
void sortWords(string *wordsArr, const int size);

//prints the array of words
void printWordsArr(string *wordsArr, const int size, string type);

//generates a sentence using the words in the array
void generateSentence(string *sentence,
                      const string *articlesArr, const int articlesSize,
                      const string *nounsArr, const int nounsSize,
                      const string *verbsArr, const int verbsSize,
                      const string *prepsArr, const int prepsSize);
