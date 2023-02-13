#include <iostream>
#include <fstream>

using namespace std;

void task1(string numbersFile);

void answerIntegerQuestions(const int num, bool *isMultiple, bool *isSumEven, bool *isPrime);

bool answerMultiple(const int num);

bool answerSumEven(const int num);

bool answerPrime(const int num);

void task2();

bool findWinningLotteryTicket(const int winningTicketNum, const int *playerNumbers, const int numPlayerNumbers);

void task3(string wordsFile);

string *createWordsArray(ifstream &inFile, const int size);

void sortWords(string *wordsArr, const int size);

void printWordsArr(string *wordsArr, const int size, string type);

void generateSentence(string *sentence,
                      const string *articlesArr, const int articlesSize,
                      const string *nounsArr, const int nounsSize,
                      const string *verbsArr, const int verbsSize,
                      const string *prepsArr, const int prepsSize);
