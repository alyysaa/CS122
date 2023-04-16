#ifndef CALCULATOR_H
#define CALCULATOR_H

// both .h and .cpp are needed because of where the template implementations are (.cpp includes the .h)
#include "Stack.cpp"

#include <iostream>
#include <fstream>
#include <functional>
#include <unordered_map>



class Calculator {
private:
    //unordered map for function pointers
    const std::unordered_map<char, std::function<long(long, long)>> opFunc = {
        {'+', [](long a, long b) { return a + b; }},
        {'-', [](long a, long b) { return a - b; }},
        {'*', [](long a, long b) { return a * b; }},
        {'/', [](long a, long b) { return b == 0 ? throw std::invalid_argument("Division by zero ") : a / b; }},
        {'%', [](long a, long b) { return b <= 0 ? throw std::invalid_argument("Cannot mod by number <=0 ") : a % b; }},
        {'^', [](long a, long b) { return pow(a, b); }}
    };

    //unordered map for precedence
    typedef std::pair<int, int> precPair;
    const std::unordered_map<char, precPair> opPrec = {
        {'+', {1, 2}},
        {'-', {1, 2}},
        {'*', {3, 4}},
        {'/', {3, 4}},
        {'%', {3, 4}},
        {'^', {6, 5}},
        {'(', {7, 0}},
        {')', {-1, -1}} //this is a dummy value, it will never be used
    };

    //unordered map for variables, key is the variable name, value is the value
    std::unordered_map<std::string, long> varMap;


public:

    /// @copybrief infixToPostfix(const std::string)
    std::string infixToPostfix(const std::string);

    /// @copybrief evaluatePostfix(const std::string)
    long evaluatePostfix(const std::string);

    /// @copybrief calculate(const std::string)
    long calculate(const std::string);

    /// @copybrief calcFilePrint(const std::string, const std::string)
    void calcFilePrint(const std::string filename= "input.txt", const std::string delim = "#", std::ostream &out = std::cout);

    /// @copybrief setVar(const std::string, const long)
    void setVar(const std::string, const long);

};


#endif