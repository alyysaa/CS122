#include "PA9.h"

/// @brief main for PA9. Tests all functions, with optional command line arguments
/// @param argv -n to not wait for user input between tasks, -v for verbose bonus task, -b to only run bonus task
/// @return 0
int main(int argc, char *argv[]) {

    //if exists, convert arg[1] to a string
    if (argc > 1) {
        std::string arg = "";
        bool wait = true;
        bool bonusVerbose = false;
        bool bonusOnly = false;
        arg = argv[1];
        if (arg[0] == '-') {
            wait = arg.substr(1).find_first_of("n") == std::string::npos;
            bonusVerbose = arg.substr(1).find_first_of("v") != std::string::npos;
            bonusOnly = arg.substr(1).find_first_of("b") != std::string::npos;
        }
        runAllTasks(wait, bonusVerbose, bonusOnly);

    }
    else runAllTasks();


    return 0;
}