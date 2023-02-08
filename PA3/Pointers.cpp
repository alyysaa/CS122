#include "Pointers.h"

void task1(string numbersFile)
{
  ifstream inFile(numbersFile);
  if (!inFile)
  {
    cout << "Task 1: Error opening file: " << numbersFile << endl;
    exit(-1);
  }
  int num;
  bool isMultiple, isSumEven, isPrime;
  cout << "Task 1: " << endl;
  while (inFile >> num)
  {
    answerIntegerQuestions(num, &isMultiple, &isSumEven, &isPrime);
    cout << "\t" << num << " is ";
    if (isMultiple)
      cout << "a multiple of 7, 11, or 13, ";
    else
      cout << "not a multiple of 7, 11, or 13, ";
    if (isSumEven)
      cout << "sum of its digits is even, ";
    else
      cout << "sum of its digits is odd, ";
    if (isPrime)
      cout << "and is prime." << endl;
    else
      cout << "and is not prime." << endl;
  }
}

void answerIntegerQuestions(const int num, bool *isMultiple, bool *isSumEven, bool *isPrime)
{
  *isMultiple = answerMultiple(num);
  *isSumEven = answerSumEven(num);
  *isPrime = answerPrime(num);
}

bool answerMultiple(const int num)
{
  if (num == 0)
  {
    return false;
  }
  return num % 7 == 0 || num % 11 == 0 || num % 13 == 0;
}

bool answerSumEven(const int num)
{
  int sum = 0;
  int temp = num;
  while (temp > 0)
  {
    sum += temp % 10;
    temp /= 10;
  }
  return sum % 2 == 0;
}

bool answerPrime(const int num)
{
  if (num <= 1)
    return false;
  for (int i = 2; i < num / 2; i++)
  {
    if (num % i == 0)
      return false;
  }
  return true;
}

void task2()
{
  int winningTicketNum;
  const int numPlayerNumbers = 10;
  const int playerNumbers[numPlayerNumbers] = {13579, 26791, 26792, 33445, 55555, 62483, 77777, 79422, 85647, 93121};

  cout << "Task 2: " << endl;
  //ask user for input of a five digit integer for the winning lottery ticket number
  cout << "\tEnter the weekly five digit winning lottery number: ";
  cin >> winningTicketNum;
  if (findWinningLotteryTicket(winningTicketNum, playerNumbers, numPlayerNumbers))
  {
    cout << "\tThe winning lottery ticket number " << winningTicketNum << " was purchased by a player." << endl;
  }
  else
  {
    cout << "\tThe winning lottery ticket number " << winningTicketNum << " was not purchased by a player." << endl;
  }

}

bool findWinningLotteryTicket(const int winningTicketNum, const int *playerNumbers, const int numPlayerNumbers)
{
  for (int i = 0; i < numPlayerNumbers; i++)
  {
    if (*(playerNumbers + i) == winningTicketNum)
    {
      return true;
    }
  }
  return false;
}

void task3(string wordsFile)
{
  ifstream inFile(wordsFile);
  if (!inFile)
  {
    cout << "Task 3: Error opening file" << endl;
    exit(-1);
  }
  int numWords;
  inFile >> numWords;
  string *words = createWordsArray(inFile, numWords);
  cout << "Task 3: " << endl;
  for (int i = 0; i < numWords; i++)
  {
    cout << "\t" << *(words + i) << endl;
  }
}

string* createWordsArray(ifstream &inFile, const int size)
{
  string *words;




  return words;
}

void generateSentence(string *sentence, const string *articlesArr, const int articlesSize, const string *nounsArr, const int nounsSize, const string *verbsArr, const int verbsSize, const string *prepsArr, const int prepsSize)
{

}