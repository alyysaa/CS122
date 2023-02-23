#include "Pointers.h"

//runs task 1, calling answerIntegerQuestions
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

//calls the other functions to answer the questions
void answerIntegerQuestions(const int num, bool *isMultiple, bool *isSumEven, bool *isPrime)
{
  *isMultiple = answerMultiple(num);
  *isSumEven = answerSumEven(num);
  *isPrime = answerPrime(num);
}

//returns true if num is a multiple of 7, 11, or 13, false otherwise
//excludes negative numbers and 0
bool answerMultiple(const int num)
{
  if (num >= 7)
  {
    return false;
  }
  return num % 7 == 0 || num % 11 == 0 || num % 13 == 0;
}

//returns true if the sum of the digits of num is even, false otherwise
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

//returns true if num is prime, false otherwise
//not very efficient, but that's a problem for another time
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

//runs task 2, calling findWinningLotteryTicket
void task2()
{
  int winningTicketNum;
  const int numPlayerNumbers = 10;
  const int playerNumbers[numPlayerNumbers] = {13579, 26791, 26792, 33445, 55555, 62483, 77777, 79422, 85647, 93121};

  cout << "Task 2: " << endl;
  // ask user for input of a five digit integer for the winning lottery ticket number
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

//runs task 3, calling the other functions as needed
void task3(string wordsFile)
{
  ifstream inFile(wordsFile);
  if (!inFile)
  {
    cout << "Task 3: Error opening file" << endl;
    exit(-1);
  }
  // read the number of sentences to generate
  int numSentences;
  inFile >> numSentences;

  int numArticles, numNouns, numVerbs, numPreps;
  string *articlesArr, *nounsArr, *verbsArr, *prepsArr;
  //point all the arrays to null
  articlesArr = nounsArr = verbsArr = prepsArr = nullptr;
  string temp;

  // for each type of word in the file, create an array of words.
  // for example, if the file contains 5 articles, create an array of 5 articles
  do
  {
    inFile >> temp;
    //convert temp to lower case
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    if (temp == "articles")
    {
      inFile >> numArticles;
      articlesArr = createWordsArray(inFile, numArticles);
    }
    else if (temp == "nouns")
    {
      inFile >> numNouns;
      nounsArr = createWordsArray(inFile, numNouns);
    }
    else if (temp == "verbs")
    {
      inFile >> numVerbs;
      verbsArr = createWordsArray(inFile, numVerbs);
    }
    else if (temp == "prepositions")
    {
      inFile >> numPreps;
      prepsArr = createWordsArray(inFile, numPreps);
    }

  } while (!inFile.eof());
  //if any of the arrays are null, exit with error
  if (articlesArr == nullptr || nounsArr == nullptr || verbsArr == nullptr || prepsArr == nullptr)
  {
    cout << "Task 3: Error reading file, one or more word types not found" << endl;
    exit(-1);
  }

  cout << "Task 3: " << endl;
  cout << "Word Bank: " << endl;
  printWordsArr(articlesArr, numArticles, "Articles");
  printWordsArr(nounsArr, numNouns, "Nouns");
  printWordsArr(verbsArr, numVerbs, "Verbs");
  printWordsArr(prepsArr, numPreps, "Prepositions");
  cout << "\t" << numSentences << " sentences generated from the file " << wordsFile << endl;

  // generate the sentences
  for (int i = 0; i < numSentences; i++)
  {
    string sentence;
    generateSentence(&sentence, articlesArr, numArticles, nounsArr, numNouns, verbsArr, numVerbs, prepsArr, numPreps);
    cout << "\t" << sentence << endl;
  }
}

string *createWordsArray(ifstream &inFile, const int size)
{
  string *words = new string[size];
  for (int i = 0; i < size; i++)
  {
    inFile >> *(words + i);
  }
  sortWords(words, size);
  return words;
}

void sortWords(string *words, const int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      if (words[i] > words[j])
      {
        string temp = words[i];
        words[i] = words[j];
        words[j] = temp;
      }
    }
  }
}

void printWordsArr(string *words, const int size, string type)
{
  cout << "\t" << type << ": (" << size << ")";
  for (int i = 0; i < size; i++)
  {
    cout << " " << words[i];
  }
  cout << endl << endl;
}

void generateSentence(string *sentence, const string *articlesArr, const int articlesSize, const string *nounsArr, const int nounsSize, const string *verbsArr, const int verbsSize, const string *prepsArr, const int prepsSize)
{
  int article1 = rand() % articlesSize;
  int noun1 = rand() % nounsSize;
  int verb = rand() % verbsSize;
  int prep = rand() % prepsSize;
  int article2 = rand() % articlesSize;
  int noun2 = rand() % nounsSize;
  string first = articlesArr[article1];
  first[0] = toupper(first[0]);
  *sentence = "" + first + " " + nounsArr[noun1] + " " + verbsArr[verb] + " " + prepsArr[prep] + " " + articlesArr[article2] + " " + nounsArr[noun2] + ".";
}