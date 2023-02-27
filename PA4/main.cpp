#include "Structs.h"
#include <fstream>

int main(int argc, char* argv[]) {
    histogramInputLoop();
    if (argc > 1) {
        takePackageInventory(argv[1]);
    } else {
        cout << "No file specified for package inventory." << endl;
    }

    return 0;
}