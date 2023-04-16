#include "Calculator.h"

/// @brief converts the given infix string to postfix
/// @param str string to convert
/// @return string in postfix form
std::string Calculator::infixToPostfix(const std::string str) {
    std::string postfix = "";
    Stack<char> opStack;
    for (char c : str) {
        if (opPrec.find(c) != opPrec.end()) { //if c is an operator
            if (c == '(') {
                opStack.push(c);
                continue; //don't add a space after the (
            }
            else if (c == ')') {
                while (opStack.peek() != '(') {
                    postfix += opStack.pop();
                }
                opStack.pop();
                continue; //don't add a space after the )
            }
            else {
                while (!opStack.isEmpty() && opPrec.at(opStack.peek()).second >= opPrec.at(c).first) {
                    postfix += opStack.pop();
                }
                opStack.push(c);
            }
            postfix += ' ';
        }
        else {
            if (c != ' ')
                postfix += c;
        }
    }
    while (!opStack.isEmpty()) {
        postfix += opStack.pop();
    }
    return postfix;
}

/// @brief evaluates a postfix string, returns the result
/// @param s postfix string to calculate
/// @return value of calculated postfix string
long Calculator::evaluatePostfix(const std::string s) {
    if (s.empty()) {
        std::cerr << "ERROR: Empty string ";
        return 0;
    }

    Stack<long> numStack;
    for (char c : s) {
        if (opPrec.find(c) != opPrec.end()) { //if c is an operator
            try {
                long b = numStack.pop();
                long a = numStack.pop();
                numStack.push(opFunc.at(c)(a, b));
            }
            catch (std::exception &e) {
                std::cerr << "ERROR: " << e.what();
                return 0;
            }
        }
        else if (isdigit(c)) {
            numStack.push(c - '0');
        }
        else if (isalpha(c)) {
            if (varMap.find(std::string(1, c)) != varMap.end()) {
                numStack.push(varMap.at(std::string(1, c)));
            }
            else {
                std::cerr << "ERROR: Variable " << c << " not found" << std::endl;
                return 0;
            }
        }
    }
    return numStack.isEmpty() ? 0 : numStack.pop();
}

/// @brief evaluates the given infix string, returns the result
/// @param str string to calculate
/// @return value of calculated infix string
long Calculator::calculate(const std::string str) {
    return evaluatePostfix(infixToPostfix(str));
}

/// @brief calculates all variables, then all expressions in the given file, outputting them to the console
/// @param filename name of file to read, defaults to "input.txt"
/// @param delim delimiter between variables and expressions, defaults to "#"
/// @param out output stream to write to, defaults to std::cout
void Calculator::calcFilePrint(const std::string filename, const std::string delim, std::ostream &out) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (line == delim)
            break;
        try {
            std::string varName = line.substr(0, line.find_first_of("= "));
            std::string varValue = line.substr(line.find_first_of("= ") + 1);
            if (varValue.find_first_not_of("-0123456789") == std::string::npos) {
                varMap[varName] = std::stol(varValue);
            }
            else {
                varMap[varName] = calculate(varValue);
            }
        }
        catch (std::invalid_argument e) {
            std::cerr << "ERROR at line: \"" << line << "\" " << e.what() << std::endl;
        }
    }

    while (std::getline(inFile, line)) {
        if (line == "") continue; //skip blanks
        if (line == delim)
            break;
        try {
            std::string post = infixToPostfix(line);
            out << line << "\t-> " << post << "\t= " << evaluatePostfix(post) << std::endl << std::endl;
        }
        catch (std::invalid_argument e) {
            std::cerr << "ERROR at line: \"" << line << "\" " << e.what() << std::endl;
        }
    }

}

/// @brief sets the given variable to the given value
/// @param varName name of variable
/// @param varValue value of variable
void Calculator::setVar(const std::string varName, const long varValue) {
    varMap[varName] = varValue;
}
