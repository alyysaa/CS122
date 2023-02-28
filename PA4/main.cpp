#include "Structs.h"

int main(int argc, char* argv[]) {
    histogramInputLoop();
    if (argc > 1) {
        takePackageInventory(argv[1]);
    } else {
        cout << "No file specified for package inventory." << endl;
    }
    cout << "Press enter to exit.";
    system("read");
    return 0;
}