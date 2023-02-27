#include "Structs.h"

//  #####   ##    ####  #    #     ####  #    # ######
//    #    #  #  #      #   #     #    # ##   # #
//    #   #    #  ####  ####      #    # # #  # #####
//    #   ######      # #  #      #    # #  # # #
//    #   #    # #    # #   #     #    # #   ## #
//    #   #    #  ####  #    #     ####  #    # ######

// task 1 driver, prompts user for strings and outputs a histogram of the letter occurences
void histogramInputLoop() {
    string s;
    while (1) {
        cout << "Enter a string (or \"-q\" to quit): ";
        getline(cin, s);
        if (s == "-q") {
            break;
        }
        occuranceHistogram(s);
    }
}

// outputs a histogram of the letter occurences in letterOccs
void occuranceHistogram(string s) {
    int maxCount;
    double maxFreq;
    char maxC;
    LetterOccurrence letterOccs[NUM_LETTERS];
    processString(s, letterOccs);
    computeMaximumOccurences(letterOccs, &maxC, &maxCount, &maxFreq);
    outputHistogram(letterOccs, s, maxC, maxCount, maxFreq);
}

// clears letterOccs and computes the count and frequency of each letter in s
void processString(const string s, LetterOccurrence letterOccs[]) {
    // clear letterOccs
    for (int i = 0; i < NUM_LETTERS; i++) {
        letterOccs[i].count = 0;
        letterOccs[i].frequency = 0.0;
    }

    // count letters
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            letterOccs[s[i] - 'A'].count++;
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            letterOccs[s[i] - 'a' + 26].count++;
        }
    }
    // compute frequencies
    computeFrequencies(letterOccs);
}

// computes the frequency of each letter in letterOccs
void computeFrequencies(LetterOccurrence letterOccs[]) {
    int total = 0;
    for (int i = 0; i < NUM_LETTERS; i++) {
        total += letterOccs[i].count;
    }
    for (int i = 0; i < NUM_LETTERS; i++) {
        letterOccs[i].frequency = (double)letterOccs[i].count / total;
    }
}

// computes the maximum occurence of a letter in letterOccs
void computeMaximumOccurences(const LetterOccurrence letterOccs[], char *c, int *count, double *freq) {
    int max = letterOccs[0].count;
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (letterOccs[i].count > max) {
            max = letterOccs[i].count;
            if (i < 26) {
                *c = i + 'A';
            } else {
                *c = i - 26 + 'a';
            }
            *count = letterOccs[i].count;
            *freq = letterOccs[i].frequency;
        }
    }
}

// outputs a histogram of the letter occurences in letterOccs
void outputHistogram(const LetterOccurrence letterOccs[], const string s, const char maxC, const int maxCount, const double maxFreq) {
    cout << "Letter frequency histogram for string \"" << s << "\":" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // outputting histogram rows
    for (int i = maxCount; i > 0; i--) {
        for (int j = 0; j < NUM_LETTERS; j++) {
            if (letterOccs[j].count >= i) {
                cout << "*";
            } else {
                cout << " ";
            }
            cout << " ";
        }
        cout << endl;
    }

    // outputting histogram labels
    for (int i = 0; i < 26; i++) {
        cout << (char)(i + 'A') << " ";
    }
    for (int i = 0; i < 26; i++) {
        cout << (char)(i + 'a') << " ";
    }
    cout << endl;

    cout << "---------------------------------------------------------------" << endl;

    // outputting maximum letter occurence
    cout << "Maximum letter occurence: " << maxC << " (" << maxCount << " times, " << maxFreq * 100 << "%)" << endl;
}


//  #####   ##    ####  #    #    ##### #    #  ####
//    #    #  #  #      #   #       #   #    # #    #
//    #   #    #  ####  ####        #   #    # #    #
//    #   ######      # #  #        #   # ## # #    #
//    #   #    # #    # #   #       #   ##  ## #    #
//    #   #    #  ####  #    #      #   #    #  ####

// task 2 driver, loads packages from a file and computes package stats
void takePackageInventory(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }

    string driverName;
    int numPackages;
    // load packages
    Package *packages = loadPackages(inFile, &driverName, &numPackages);

    // compute package stats
    int heaviestId;
    double heaviestWeight;
    double avgWeight;
    computePackageStats(packages, numPackages, &heaviestId, &heaviestWeight, &avgWeight);

    int maxLen;
    computeLongestLen(packages, numPackages, &maxLen);

    // output package stats
    printPackageInventory(packages, numPackages, maxLen, driverName, heaviestId, heaviestWeight, avgWeight);
}

// loads packages from inFile, stores driver name in driverName, stores number of packages in numPackages
Package *loadPackages(ifstream &inFile, string *driverName, int *numPackages) {
    string line;
    // read driver name
    getline(inFile, line);
    *driverName = line;
    //count number of packages
    *numPackages = 0;
    while (getline(inFile, line)) {
        if (line == "\r") {
            (*numPackages)++;
        }

    }
    inFile.clear();
    inFile.seekg(0,ios::beg);
    getline(inFile, line); //skip driver name
    Package *packages = new Package[*numPackages];
    for (int i = 0; i < *numPackages; i++) {
        getline(inFile, line); //skip blank line
        try {
            // read package id
            inFile >> line;
            packages[i].id = stoi(line);
            // read package weight
            inFile >> line;
            packages[i].weight = stod(line);
            // read package width
            inFile >> line;
            packages[i].width = stoi(line);
            //read package length
            inFile >> line;
            packages[i].length = stoi(line);
            //read package height
            inFile >> line;
            packages[i].height = stoi(line);
        } catch (exception e) {
            cout << "Error reading package " << i+1 << endl;
        }

    }

    return packages;
}


// computes package stats
void computePackageStats(const Package *packages, const int numPackages, int *heaviestId, double *heaviestWeight, double *avgWeight) {
    *heaviestId = packages[0].id;
    *heaviestWeight = packages[0].weight;
    *avgWeight = 0;
    for (int i = 0; i < numPackages; i++) {
        if (packages[i].weight > *heaviestWeight) {
            *heaviestId = packages[i].id;
            *heaviestWeight = packages[i].weight;
        }
        *avgWeight += packages[i].weight;
    }
    *avgWeight /= (double)numPackages;
}

// computes the longest legnth of a string needed to show a package (for chart printing)
void computeLongestLen(const Package *packages, const int numPackages, int *maxLen) {
    *maxLen = 0;
    for (int i = 0; i < numPackages; i++) {
        if (to_string(packages[i].id).length() > *maxLen) {
            *maxLen = to_string(packages[i].id).length();
        }
        if (to_string(packages[i].weight).length() > *maxLen) {
            *maxLen = to_string(packages[i].weight).length();
        }
        if (to_string(packages[i].width).length() > *maxLen) {
            *maxLen = to_string(packages[i].width).length();
        }
        if (to_string(packages[i].length).length() > *maxLen) {
            *maxLen = to_string(packages[i].length).length();
        }
        if (to_string(packages[i].height).length() > *maxLen) {
            *maxLen = to_string(packages[i].height).length();
        }
    }
}

void printPackageInventory(const Package *packages, const int numPackages, const int maxLen, const string driverName, const int heaviestId, const double heaviestWeight, const double avgWeight) {
    cout << "Package inventory for driver: " << driverName << endl;
    cout << "Package count: " << numPackages << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout.width(maxLen);
    cout << "ID";
    cout.width(maxLen);
    cout << "Weight";
    cout.width(maxLen);
    cout << "Width";
    cout.width(maxLen);
    cout << "Length";
    cout.width(maxLen);
    cout << "Height" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 0; i < numPackages; i++) {
        cout.width(maxLen);
        cout << packages[i].id;
        cout.width(maxLen);
        cout << packages[i].weight;
        cout.width(maxLen);
        cout << packages[i].width;
        cout.width(maxLen);
        cout << packages[i].length;
        cout.width(maxLen);
        cout << packages[i].height << endl;
    }

    //stats
    cout << "---------------------------------------------------------------" << endl;
    cout << "Heaviest package: " << heaviestId << " (" << heaviestWeight << " lbs)" << endl;
    cout << "Average package weight: " << avgWeight << " lbs" << endl;


}