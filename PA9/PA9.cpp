#include "PA9.h"




/// @brief recursive function that counts the number of digits in a string
/// @param s string to count digits in
/// @return number of digits in s
int countDigits(std::string s) {
    if (s.length() == 0) {
        return 0;
    }
    else if (isdigit(s[0])) {
        return 1 + countDigits(s.substr(1));
    }
    else {
        return countDigits(s.substr(1));
    }
}

/// @brief recursive function that sums the digits in an integer
/// @param n integer to sum digits of
/// @return sum of digits in n
int sumDigits(int n) {
    return n == 0 ? 0 : n % 10 + sumDigits(n / 10);
}

/// @brief recursive function that determines if a string is a palindrome
/// @param s string to check if palindrome
/// @return true if s is a palindrome, false otherwise
bool isPalindrome(std::string s) {
    //clear all whitespace
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());

    //convert to lowercase
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    if (s.length() == 0 || s.length() == 1) {
        return true;
    }
    else if (s[0] == s[s.length() - 1]) {
        return isPalindrome(s.substr(1, s.length() - 2));
    }
    else {
        return false;
    }
}

/// @brief generate all possible substrings of a given string
/// @param s string to generate substrings of
/// @param v vector to store substrings in
void generateSubstrings(std::string s, std::vector<std::string> &v) {
    if (s.length() == 0) return;
    substringHelper(s, v, 0, 0);
    v.push_back(""); //empty string
}

/// @brief helps generateSubstrings(), recursively generates substrings of a given string
/// @param s string to generate substrings of
/// @param v vector to store substrings in
/// @param start current starting index of substring
/// @param end current ending index of substring
void substringHelper(std::string s, std::vector<std::string> &v, int start, int end) {
    if (start >= s.length()) { return; }
    else if (end == s.length()) {
        substringHelper(s, v, start + 1, start + 1);
    }
    else {
        v.push_back(s.substr(start, end - start + 1));
        substringHelper(s, v, start, end + 1);
    }
}

/// @brief attempts to traverse a char "maze" recursively, attempting to find a path from (0,0) to (7,7)
/// @param maze maze to traverse
/// @param sol solution array to store path in, if found
/// @param steps number of steps taken to reach current position, final value is number of steps taken to reach end if path is found
/// @param row current row
/// @param col current column
/// @return true if path is found, false otherwise
bool traverseMaze(char maze[8][8], Coordinate sol[], int *steps, bool verbose, int row, int col) {
    if (verbose) {
        system("clear");
        std::cout << "Traversing...\nSteps taken: " << *steps << "\n";

        displayMaze(maze);
        //sleep thread for a bit, both allows ctrl-c to work and the traversal to be shown
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    //base case, when maze is solved
    if (row == 7 && col == 7) {
        sol[*steps] = { row, col };
        (*steps)++;
        maze[row][col] = 'T';
        return true;
    }
    if (maze[row][col] == 'X') { //basically only if (0,0) is an X
        return false;
    }
    else {
        sol[*steps] = { row, col };
        (*steps)++;

        if (row < 7 && maze[row + 1][col] == ' ') {
            maze[row][col] = 'S'; //south
            if (traverseMaze(maze, sol, steps, verbose, row + 1, col)) {
                return true;
            }
        }
        if (col < 7 && maze[row][col + 1] == ' ') {
            maze[row][col] = 'E'; //east
            if (traverseMaze(maze, sol, steps, verbose, row, col + 1)) {
                return true;
            }
        }
        if (row > 0 && maze[row - 1][col] == ' ') {
            maze[row][col] = 'N'; //north
            if (traverseMaze(maze, sol, steps, verbose, row - 1, col)) {
                return true;
            }
        }
        if (col > 0 && maze[row][col - 1] == ' ') {
            maze[row][col] = 'W'; //west
            if (traverseMaze(maze, sol, steps, verbose, row, col - 1)) {
                return true;
            }
        }
        maze[row][col] = ' ';
        (*steps)--;
        return false;
    }


}

/// @brief displays a char "maze" to the console
/// @param maze "maze" to be displayed
void displayMaze(char maze[8][8]) {
    std::cout << "  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
        for (char j : maze[i]) {
            switch (j) {
            case 'N':
                std::cout << UP_ARROW << " ";
                break;
            case 'E':
                std::cout << RIGHT_ARROW << " ";
                break;
            case 'S':
                std::cout << DOWN_ARROW << " ";
                break;
            case 'W':
                std::cout << LEFT_ARROW << " ";
                break;
            case 'T':
                std::cout << TARGET << " ";
                break;
            case 'X':
                std::cout << WALL << " ";
                break;
            default:
                std::cout << j << " ";
                break;
            }
        }
        std::cout << std::endl;
    }

}

// ###############    ###############    ###############    ###############    ###############
// ###############    ###############    ###############    ###############    ###############
//      #####         #####              #####                   #####         #####
//      #####         #####              #####                   #####         #####
//      #####         ###########        ###############         #####         ###############
//      #####         ###########        ###############         #####         ###############
//      #####         #####                        #####         #####                   #####
//      #####         #####                        #####         #####                   #####
//      #####         ###############    ###############         #####         ###############
//      #####         ###############    ###############         #####         ###############

/// @brief testing task 1 (countDigits())
void runTask1() {
    std::cout << "\n---------------------Task 1---------------------\n";
    std::string strings[] = { "abc123", "abc", "123", "a1b2c3", "a", "1", "abc123xyz", "abc123xyz123", "abc123xyz123abc", "abc123xyz123abc123xyz123abc" };
    for (std::string s : strings) {
        std::cout << "countDigits(" << s << ") = " << countDigits(s) << std::endl;
    }
    std::cout << "------------------------------------------------\n";
}

/// @brief testing task 2 (sumDigits())
void runTask2() {
    std::cout << "\n---------------------Task 2---------------------\n";
    int numbers[] = { 123, 1, 123456789, 1234567890, 0, 1720989164 };
    for (int n : numbers) {
        std::cout << "sumDigits(" << n << ") = " << sumDigits(n) << std::endl;
    }
    std::cout << "------------------------------------------------\n";
}

/// @brief testing task 3 (isPalindrome())
void runTask3() {
    std::cout << "\n---------------------Task 3---------------------\n";
    std::string strings[] = { "racecar", "racepar", "race car", "dead", "LEVEL", "lEvEL", "madam im adam", "absolutely not a palindrome" };
    for (std::string s : strings) {
        std::cout << "isPalindrome(" << s << ") = " << isPalindrome(s) << std::endl;
    }
    std::cout << "------------------------------------------------\n";
}

/// @brief testing task 4 (getMaxValue())
void runTask4() {
    std::cout << "\n---------------------Task 4---------------------\n";
    int nums[] = { 1,2,3,10,20,-1274,14,15,9 };
    LinkedList ll(nums, 9);

    std::cout << "Original list: ";
    ll.displayList();
    int max = ll.getMaxValue();
    std::cout << "Max value: " << max << std::endl;
    std::cout << "------------------------------------------------\n";
}

/// @brief testing task 5 (generateSubstrings())
void runTask5() {
    std::cout << "\n---------------------Task 5---------------------\n";
    std::string strings[] = { "abc", "bird", "dog", "cat", "a", "b", "c", "d", "ab", "bc", "cd", "abcde" };
    for (std::string s : strings) {
        std::vector<std::string> v;
        generateSubstrings(s, v);
        std::cout << "generateSubstrings(" << s << ") = ";
        for (int i = 0; i < v.size(); i++) {
            std::cout << "\"" << v[i] << "\" ";

        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------------------------\n";
}

/// @brief testing task 6 (traverseMaze())
void runBONUSTask(bool verbose) {
    Coordinate sol[64];
    char maze[8][8];
    srand(time(NULL));
    while (1) {
        std::cout << "\n----------------------BONUS---------------------\n";
        createRandomMaze(maze);
        int steps = 0;
        displayMaze(maze);
        if (traverseMaze(maze, sol, &steps, verbose)) {
            std::cout << "Solution found!\n";
            std::cout << "Steps taken: " << steps << "\n";
            displayMaze(maze);
            for (int i = 0; i < steps; i++) {
                std::cout << "(" << sol[i].row << ", " << sol[i].col << ")\n";
            }
        }
        else {
            std::cout << "No solution found.\n";
            if (verbose) displayMaze(maze);
        }
        std::cout << "------------------------------------------------\n";
        contCheck(); // check if user wants to continue, entering any text will break
    }
}

/// @brief creates a random char "maze" with 8 rows and 8 columns
/// @param maze maze to be filled
void createRandomMaze(char maze[8][8]) {
    // how often to place a wall, 1 in freq chances
    // higher freq = less walls, lower freq = more walls
    // feel free to change for tests
    int freq = 4;

    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            maze[i][j] = (rand() % freq == 0) ? 'X' : ' ';
        }
    }
    maze[0][0] = ' ';
    maze[7][7] = ' ';
}

/// @brief runs all tasks in order, with optional wait between each task
/// @param wait option to wait for user input between each task, default true
/// @param bonusVerbose option to show maze traversal for bonus task, default false 
/// @param onlyBonus option to only run bonus task, default false
void runAllTasks(bool wait, bool bonusVerbose, bool onlyBonus) {
    if (onlyBonus) {
        runBONUSTask(bonusVerbose);
        return;
    }
    runTask1();
    if (wait) {
        std::cout << "Enter to continue, any text to exit: ";
        contCheck();
    }
    runTask2();
    if (wait) contCheck();
    runTask3();
    if (wait) contCheck();
    runTask4();
    if (wait) contCheck();
    runTask5();
    if (wait) contCheck();
    runBONUSTask(bonusVerbose);
}

/// @brief checks if user wants to continue, if not exits program. Entering any text will exit the program
void contCheck() {
    std::string choice;
    getline(std::cin, choice);
    if (choice != "") exit(0);

}