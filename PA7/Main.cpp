#include "Calculator.h"

using namespace std;

//provides a way to easily test and output results of infixToPostfix and evaluatePostfix
void testCalc(string s, Calculator &calc) {
    cout << s << " -> ";
    s = calc.infixToPostfix(s);
    cout << s << " -> ";
    cout << calc.evaluatePostfix(s) << endl;
}

int main(int argc, char **argv) {

    Calculator calc;

    if (argc > 1)
        calc.calcFilePrint(argv[1]);
    else //fill in whatever file you want to test in this function, currently the default "input.txt"
        calc.calcFilePrint();
    // #####################################################
    // #####################################################
    // ########## TEST CASES ###############################
    // #####################################################
    // #####################################################
    //invalid input cases, uncomment to test
    testCalc("2**3", calc);
    testCalc("2*3+", calc);
    testCalc("2*3+4*5+", calc);
    testCalc("", calc);

    //uncomment to test these cases, most are already in input.txt

    // testCalc("1 + 2", calc);
    // testCalc("1 + 2 * 3", calc);
    // testCalc("1 + 2 * 3 + 4", calc);
    // testCalc("1 + 2 * 3 + 4 * 5", calc);
    // testCalc("1 + 2 * 3 + 4 * 5 + 6", calc);
    // testCalc("1 + 2 * 3 + 4 * 5 + 6 * 7", calc);
    // testCalc("1 + 2 * 3 + 4 * 5 + 6 * 7 + 8", calc);
    // testCalc("1^2 + 2^3 * 3^4 + 4^5 * 5^6 + 6^7 * 7^8 + 8^9", calc);
    // testCalc("(1 + 2) * 3", calc);
    // testCalc("(1 + 2) * (3 + 4)", calc);
    // testCalc("1^2 * (3-4)*5", calc);
    // //test mod and div
    // testCalc("1 % 2 * 3 / 4", calc);
    // testCalc("1 % 2 * 3 / 4 + 5", calc);
    // testCalc("1/0", calc);
    // testCalc("3-2", calc);
    // testCalc("2-3", calc);
    // testCalc("200 ^ 2", calc);
    // testCalc("10 + 20 * 6", calc);

    //above strings without spaces, uncomment to test

    // testCalc("1+2", calc);
    // testCalc("1+2*3", calc);
    // testCalc("1+2*3+4", calc);
    // testCalc("1+2*3+4*5", calc);
    // testCalc("1+2*3+4*5+6", calc);
    // testCalc("1+2*3+4*5+6*7", calc);
    // testCalc("1+2*3+4*5+6*7+8", calc);
    // testCalc("1^2+2^3*3^4+4^5*5^6+6^7*7^8+8^9", calc);
    // testCalc("(1+2)*3", calc);
    // testCalc("(1+2)*(3+4)", calc);
    // testCalc("1^2*(3-4)*5", calc);
    // //test mod and div
    // testCalc("1%2*3/4", calc);
    // testCalc("1%2*3/4+5", calc);
    // testCalc("1/0", calc);
    // testCalc("3-2", calc);
    // testCalc("2-3", calc);

    //testing variables
    calc.setVar("x", 5);
    calc.setVar("y", 10);
    calc.setVar("z", 15);
    testCalc("x + y * z", calc);
    calc.setVar("x", 10);
    testCalc("x + y * z", calc);
    calc.setVar("x", -12);
    testCalc("x + y * z", calc);
    return 0;
}