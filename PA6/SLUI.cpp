#include "SLUI.h"


/// @brief strips newlines from a string
/// @param s string to strip
void stripNewlines(string *s) {
    for (int i = 0; i < s->length(); i++) {
        if ((*s)[i] == '\n' || (*s)[i] == '\r') {
            s->erase(i, 1);
            i--;
        }
    }
}

/// @brief displays the menu of 10 options
void displayMenu() {
    cout << "Song Library Menu\n";
    cout << "Separate all inputs with a comma.\n";
    cout << "Note that all searches are not case-sensitive.\n";
    cout << "--------------------------------------------\n";
    cout << "1. Display Library\n";
    cout << "2. View This Menu\n";
    cout << "3. Load Library\n";
    cout << "4. Save Library\n";
    cout << "5. Sort Library\n";
    cout << "6. Search Library\n";
    cout << "7. Insert Song\n";
    cout << "8. Remove Song\n";
    cout << "9. Edit Song\n";
    cout << "0. Exit.\n";
    cout << "--------------------------------------------\n";

}

/// @brief gets the user's choice from the menu
/// @return integer 1-9 (0 is reserved for exit)
int getOption() {
    string input;
    cout << "Enter your choice: ";
    getline(cin, input);
    try {
        int option = stoi(input);
        if (option == 0) {
            cout << "Goodbye!\n";
            exit(0);
        }
        while (option < FIRST_OPTION || option > LAST_OPTION) {
            cout << "Invalid option. Please enter a number between " << FIRST_OPTION << " and " << LAST_OPTION << ".\n";
            cout << "To view the menu, enter 2.\n\n";
            cout << "Enter your choice: ";
            getline(cin, input);
            option = stoi(input);
            if (option == 0) {
                cout << "Goodbye!\n";
                exit(0);
            }
        }
        cout << endl;
        return option;
    }
    catch (const exception &e) {
        cout << "Invalid option. Please enter a number between " << FIRST_OPTION << " and " << LAST_OPTION << ".\n";
        cout << "To view the menu, enter 2.\n\n";
        return getOption();
    }

}

/// @brief executes user choice from the list, handles input, and calls the appropriate function
/// @param option integer 1-9, user's choice of action
/// @param lib song library to perform action on
void exeChoice(int option, SongLibrary &lib) {
    string input;
    switch (option) {
    case 1: {
        lib.displayLibrary();
        break;
    }
    case 2: {
        displayMenu();
        break;
    }
    case 3: {
        cout << "Enter the name of the file to load: ";
        getline(cin, input);
        lib.performLoad(input);
        break;
    }
    case 4: {
        cout << "Enter the name of the file to save to: ";
        getline(cin, input);
        lib.performSave(input);
        break;
    }
    case 5: {
        cout << "Enter the attribute to sort by (title, artist, genre, or rating): ";
        getline(cin, input);
        SongAttribute att = stringToSongAttribute(input);
        if (att == NIL) {
            cout << "Invalid attribute.\n";
            break;
        }
        lib.performSort(att);
        cout << "Library " << lib.isReversedString() << "sorted by " << SongAttributeStrings[att] << ".\n";
        break;
    }
    case 6: {
        cout << "Enter the attribute to search by (title, artist, genre or rating), followed by the value to search for: ";
        getline(cin, input, ',');
        SongAttribute att = stringToSongAttribute(input);
        if (att == NIL) {
            cout << "Invalid attribute.\n";
            getline(cin, input); // clear the rest of the line
            break;
        }
        cin >> ws;
        getline(cin, input);
        bool found;
        int index;
        Song *song = lib.performSearch(att, input, &found, &index);
        if (found) {
            cout << "Song found at index " << index << ":\n\t";
            song->displaySong();
        }
        else {
            cout << "Song not found.\n";
        }
        break;
    }
    case 7: {
        cout << "Enter the song's title, artist, genre, and rating (in that order): ";
        getline(cin, input, ',');
        string title = input;

        getline(cin, input, ',');
        input.erase(0, input.find_first_not_of(' '));
        string artist = input;

        getline(cin, input, ',');
        input.erase(0, input.find_first_not_of(' '));
        string genre = input;

        stripNewlines(&title);
        stripNewlines(&artist);
        stripNewlines(&genre);
        // no need to strip newlines from rating, since it's an int

        getline(cin, input);
        int rating;
        try {
            rating = stoi(input);
        }
        catch (const exception &e) {
            cout << "Failed to insert song, invalild rating.\n";
        }

        Song *song = new Song(title, artist, genre, rating);
        lib.performInsertSongInOrder(song);
        cout << "Song inserted.\n\t";
        song->displaySong();
        cout << endl;
        break;
    }
    case 8: {
        cout << "Enter the attribute of the song to remove, and the value of that attribute: ";
        getline(cin, input, ',');
        SongAttribute att = stringToSongAttribute(input);
        if (att == NIL) {
            cout << "Invalid attribute.\n";
            getline(cin, input);
            break;
        }
        getline(cin, input);
        input.erase(0, input.find_first_not_of(' '));
        bool found;
        int index;

        Song *song = lib.performSearch(att, input, &found, &index);

        if (found) {
            lib.performRemoveSong(song);
            cout << "Song removed.\n";
        }
        else {
            cout << "Song not found.\n";
        }
        break;
    }
    case 9: {
        cout << "Enter the attribute of the song to edit, the current value, and the new value: ";

        getline(cin, input, ',');
        input.erase(0, input.find_first_not_of(' '));
        SongAttribute att = stringToSongAttribute(input);

        getline(cin, input, ',');
        input.erase(0, input.find_first_not_of(' '));
        string oldVal = input;

        getline(cin, input);
        input.erase(0, input.find_first_not_of(' '));

        bool found;
        int index;
        Song *song = lib.performSearch(att, oldVal, &found, &index);
        if (found) {
            lib.performEditSong(song, att, input);
            cout << "Song edited:\n\tChanged " << SongAttributeStrings[att] << " from " << oldVal << " to " << input << ".\n";
            cout << "New song info:\n\t";
            song->displaySong();
        }
        else {
            cout << "Song not found.\n";
        }
        break;
    }
    default:
        cout << "Invalid option.\n";
        break;
    }
    cout << endl;
}

/// @brief loop for the program, displays menu and calls exeChoice
/// @param argc count of arguments (used to preload a file)
/// @param args argument values (used to preload a file)
void runMusic(int argc, char *args[]) {
    SongLibrary lib;

    if (argc > 1) {
        lib.performLoad(args[1]);
    }

    displayMenu();
    while (true) {
        exeChoice(getOption(), lib);
    }
}

/// @brief used to test the copy constructor, creates a library, copies it, sorts the copy, and displays both
void testCopy(){
    SongLibrary lib;
    lib.performLoad("library.txt");
    cout << "\n########Original library:\n\n";
    lib.displayLibrary();
    SongLibrary lib2(lib);
    lib2.performSort(ARTIST);
    cout << "\n########Copied library:\n\n";
    lib2.displayLibrary();
    cout << "\n########Original library:\n\n";
    lib.displayLibrary();

    cout << "Press enter to exit." << endl;
    system("read");
    exit(1);
}