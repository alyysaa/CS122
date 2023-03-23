#include "PA5.h"

/// @brief displays the menu to the user, lists all choices
void displayMenu() {
    cout << "\nPlease choose from the following options (choose by number):\n";
    cout << "For all multivalue inputs, separate values with a comma (,)\n";
    cout << "1) Display library\n";
    cout << "2) Load library\n";
    cout << "3) Store library\n";
    cout << "4) Sort library\n";
    cout << "5) Search library\n";
    cout << "6) Add song to library\n";
    cout << "7) Remove song from library\n";
    cout << "8) Edit song in library\n";
    cout << "9) Quit\n";
}

/// @brief gets a valid choice from user, repeats until valid
/// @return integer from 1 to 9, user's choice
int getValidChoice() {
    int choice = -1;
    string temp;
    do {
        cout << "Choice: ";
        getline(cin, temp);
        try{
            choice = stoi(temp);
        } catch (exception e) {
            cout << "That is not a valid option. Please try again.\n";
            continue;
        }
        if (choice < FIRST_OPTION || choice > LAST_OPTION) {
            cout << "That is not a valid option. Please try again.\n";
        }
    } while (choice < FIRST_OPTION || choice > LAST_OPTION);
    return choice;
}

/// @brief calls functions from SongLibrary based on user choice
/// @param choice int 1 to 9, user's choice of action
/// @param lib library to perform actions on
void executeUserChoice(int choice, SongLibrary &lib) {
    string input;
    switch (choice) {
    case 1:
        lib.displayLibrary();
        break;
    case 2:
        cout << "Enter the name of the file to load: ";
        getline(cin, input);
        lib.performLoad(input);
        break;
    case 3:
        cout << "Enter the name of the file to save to: ";
        getline(cin, input);
        lib.performSave(input);
        break;
    case 4:
        cout << "Enter the attribute to sort by (title, artist, genre, and rating): ";
        getline(cin, input);
        lib.performSort(stringToSongAttribute(input));
        break;
    case 5: {
        string value;
        cout << "Enter the attribute to search by (title, artist, genre, rating), followed by the value to search for: ";
        getline(cin, input, ',');
        getline(cin, value);
        value.erase(0, value.find_first_not_of(' ')); //trim leading whitespace
        cout << "Searching for \"" << value << "\" in \"" << input << "\"\n";
        Song s;
        int i;
        if (lib.performSearch(stringToSongAttribute(input), value, &s, &i)) {
            cout << "\nSong found at library position " << i + 1 << "\n\t";
            s.displaySong();
            cout << '\n';
        }

    }	break;
    case 6: {
        string artist, genre, rating;
        cout << "Enter the song to add in the following format: title, artist, genre, rating: ";
        getline(cin, input, ',');
        getline(cin, artist, ',');
        artist.erase(0, artist.find_first_not_of(' ')); //trim leading whitespace
        getline(cin, genre, ',');
        genre.erase(0, genre.find_first_not_of(' ')); //trim leading whitespace
        getline(cin, rating);
        rating.erase(0, rating.find_first_not_of(' ')); //trim leading whitespace
        try {
            stoi(rating);
        } catch (invalid_argument) {
            cout << "Invalid rating, must be an integer\n";
            break;
        }
        Song s = Song(input, artist, genre, stoi(rating));
        lib.performAddSong(s);
        cout << "\nSong added to library\n\t";
        s.displaySong();
    }   break;
    case 7: {
        string value;
        cout << "Enter the attribute name and value to delete from the library:";
        getline(cin, input, ',');
        getline(cin, value);
        value = convertToLowercase(value);
        value.erase(0, value.find_first_not_of(' ')); //trim leading whitespace
        Song s;
        int i;
        if (lib.performSearch(stringToSongAttribute(input), value, &s, &i)) {
            lib.performRemoveSong(i);
        }
    }   break;
    case 8: {
        string value, newValue;
        SongAttribute att;
        cout << "Enter the attribute name, current value, and new value to edit in the library:";
        getline(cin, input, ',');
        getline(cin, value, ',');
        value = convertToLowercase(value);
        value.erase(0, value.find_first_not_of(' ')); //trim leading whitespace
        getline(cin, newValue);
        newValue.erase(0, newValue.find_first_not_of(' ')); //trim leading whitespace
        att = stringToSongAttribute(input);
        Song s;
        int i;
        if (lib.performSearch(att, value, &s, &i)) {
            lib.performEditSong(i, att, newValue);
        }
    }   break;
    default:
        cout << "Unrecognized menu choice\n";
        break;
    }
}

/// @brief runs the music manager/program, user input loop, menu, and choice execution
void runMusicManager() {
    SongLibrary lib;

    cout << '\n' << "Welcome to the CPSC 122 Music Manager!!\n";
    int choice = -1;
    //lib.performLoad("library.txt"); //TODO remove
    do {
        displayMenu();
        choice = getValidChoice();
        if (choice != QUIT_OPTION) {
            executeUserChoice(choice, lib);
        }
    } while (choice != QUIT_OPTION);
    cout << "Thanks for you using the CPSC 122 Music Manager!!\n";
}