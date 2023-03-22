#include "SongLibrary.h"

/// @brief default constructor for SongLibrary class
SongLibrary::SongLibrary() {
    numSongs = 0;
    songs = NULL;
    sortAtt = TITLE;
}

/// @brief constructor including array of songs, but not sort attribute
/// @param numSongs number of songs, must be equal to size of songs array
/// @param songs array of songs, has size numSongs
SongLibrary::SongLibrary(int numSongs, Song *songs) {
    this->numSongs = numSongs;
    this->songs = songs;
    sortAtt = TITLE;
    performSort(sortAtt); //ensure array is sorted
}

/// @brief constructor including array of songs and sort attribute
/// @param numSongs number of songs, must be equal to size of songs array
/// @param songs array of songs, has size numSongs
/// @param sortAtt sort attribute to be used for library
SongLibrary::SongLibrary(int numSongs, Song *songs, SongAttribute sortAtt) {
    this->numSongs = numSongs;
    this->songs = songs;
    this->sortAtt = sortAtt;
    performSort(sortAtt); //ensure array is sorted
}

/// @brief destroys songs, sets numSongs to 0, and sets songs to NULL before destruction
SongLibrary::~SongLibrary() {
    delete[] songs;
    songs = NULL;
    numSongs = 0;
    sortAtt = NIL;
}

/// @return number of songs in library
int SongLibrary::getNumSongs() {
    return numSongs;
}

/// @return array of songs in library
Song *SongLibrary::getSongsArray() {
    return songs;
}

/// @brief displays library to console, sorted by sortAtt
void SongLibrary::displayLibrary() {
    int tw, aw, gw, rw;
    tw = 6; //length of "rating "
    aw = 7; //length of "artist "
    gw = 6; //length of "genre "
    rw = 7; //length of "rating " (not necessary unless song max rating exceeds )
    computeMaxLengths(&tw, &aw, &gw, &rw);
    cout << '\n' << "Library: " << numSongs << " songs, sorted by " << SongAttributeStrings[sortAtt] << '\n';
    formattedCout("Title", tw);
    formattedCout("Artist", aw);
    formattedCout("Genre", gw);
    formattedCout("Rating", rw);
    cout << '\n';
    for (int i = 0; i < numSongs; i++) {

        songs[i].formattedDisplay(tw, aw, gw, rw);
    }
    cout << '\n';
}

/// @brief computes the maximum length of each attribute in the library
/// @param tw title width
/// @param aw artist width
/// @param gw genre width
/// @param rw rating width
void SongLibrary::computeMaxLengths(int *tw, int *aw, int *gw, int *rw) {
    const int OFFSET = 3; //offset for the space between the attribute and the next attribute
    int comp;
    for (int i = 0; i < numSongs; i++) {
        comp = songs[i].getAttribute(TITLE).length();
        if (comp - OFFSET > *tw) {
            *tw = comp + OFFSET;
        }
        comp = songs[i].getAttribute(ARTIST).length();
        if (comp - OFFSET > *aw) {
            *aw = comp + OFFSET;
        }
        comp = songs[i].getAttribute(GENRE).length();
        if (comp - OFFSET > *gw) {
            *gw = comp + OFFSET;
        }
        comp = songs[i].getAttribute(RATING).length();
        if (comp - OFFSET > *rw) { //this isn't too helpful since all ratings will be 1 digit in this case
            *rw = comp; // offset is not necessary here, this is the last attribute
        }
    }
}

/// @brief loads songs into library from file
/// @param filename file to load from
void SongLibrary::performLoad(string filename) {
    int songsCount = 0;
    ifstream in = ifstream(filename);
    if (!in.is_open()) {
        cout << "\nFile not found\n";
        return;
    }
    string title, artist, genre, rating;
    while (!in.eof()) {
        getline(in, title);
        getline(in, artist);
        getline(in, genre);
        getline(in, rating);
        songsCount++;
        if (title == "" || artist == "" || genre == "" || rating == "") {
            cout << "Invalid file format, load failed at song " << songsCount + 1 << '\n';
            break;
        }
        performAddSong(Song(title, artist, genre, stoi(rating)));
        getline(in, title); // flush the newline
    }
    cout << '\n' << "Loaded " << songsCount << " songs from " << filename << '\n';
}

/// @brief outputs libary to file in text form
/// @param filename file to write to
void SongLibrary::performSave(string filename) {
    ofstream out = ofstream(filename);
    if (!out.is_open()) {
        cout << "Error opening file, save failed!\n";
        return;
    }
    for (int i = 0; i < numSongs; i++) {
        out << songs[i].getAttribute(TITLE) << '\n';
        out << songs[i].getAttribute(ARTIST) << '\n';
        out << songs[i].getAttribute(GENRE) << '\n';
        out << songs[i].getAttribute(RATING);
        if (i != numSongs - 1) {
            out << '\n' << '\n';
        }
    }
    cout << "\nSaved " << numSongs << " songs to " << filename << '\n';
}

/// @brief sorts library by given attribute
/// @param att attribute to sort by, updates sortAtt
void SongLibrary::performSort(SongAttribute att) {
    if (att == NIL) {
        cout << "\nInvalid sort attribute, unable to sort\n";
        return;
    }
    sortAtt = att;
    for (int i = 0; i < numSongs - 1; i++) {
        for (int j = i + 1; j < numSongs; j++) {
            if (convertToLowercase(songs[i].getAttribute(sortAtt)) > convertToLowercase(songs[j].getAttribute(sortAtt))) {
                Song temp = songs[i];
                songs[i] = songs[j];
                songs[j] = temp;
            }
        }
    }
    if (att == RATING) { // reverse the array if sorting by rating, since we want the highest rating first
        for (int i = 0; i < numSongs / 2; i++) {
            Song temp = songs[i];
            songs[i] = songs[numSongs - 1 - i];
            songs[numSongs - 1 - i] = temp;
        }
    }
    cout << "\nSorted by " << SongAttributeStrings[sortAtt] << "\n";
}

/// @brief searches for a song with the given attribute value with a binary search, returns true if found, false otherwise
/// @param att attribute to search with
/// @param searchAttributeValue value to search for
/// @param foundSong song to return if found
/// @param index index of found song
/// @return true if song with specified attribute value found, false otherwise
bool SongLibrary::performSearch(SongAttribute att, string searchAttributeValue, Song *foundSong, int *index) {
    if (att != sortAtt) {
        this->performSort(att);
    }
        
    string attVal = convertToLowercase(searchAttributeValue);
    int left = 0, right = numSongs - 1, mid = (left + right) / 2;
   
    if (att == RATING){ // since we reversed the array if sorting by rating, we need to do the same for the search
        while (left <= right) {
            if (convertToLowercase(songs[mid].getAttribute(att)) == attVal) {
                *foundSong = songs[mid];
                *index = mid;
                return true;
            } else if (convertToLowercase(songs[mid].getAttribute(att)) < attVal) {
                right = mid - 1;
            } else { // songs[mid].getAttribute(att) > attVal
                left = mid + 1;
            }
            mid = (left + right) / 2;
        }
        cout << "\nSong not found in library\n";
        return false;
    }

    while (left <= right) {
        if (convertToLowercase(songs[mid].getAttribute(att)) == attVal) {
            *foundSong = songs[mid];
            *index = mid;
            return true;
        } else if (convertToLowercase(songs[mid].getAttribute(att)) > attVal) {
            right = mid - 1;
        } else { // songs[mid].getAttribute(att) < attVal
            left = mid + 1;
        }
        mid = (left + right) / 2;
    }
    cout << "\nSong not found in library\n";
    return false;
}

/// @brief adds a new song to the library in the correct position (determined by sortAtt)
/// @param newSong song to add
void SongLibrary::performAddSong(Song newSong) {
    string att = convertToLowercase(newSong.getAttribute(sortAtt));
    Song *temp = new Song[numSongs + 1];

    int i = 0;
    if (sortAtt == RATING) { //rating is sorted in descending order
        for (int i = 0; i < numSongs; i++) {
            if (songs[i].getAttribute(sortAtt) < att) {
                break;
            }
        }
        temp[i] = newSong;
        for (; i < numSongs; i++) {
            temp[i + 1] = songs[i];
        }

    } else { // all other attributes are sorted in ascending order
        for (; i < numSongs; i++) {
            if (convertToLowercase(songs[i].getAttribute(sortAtt)) > att) {
                break;
            }
            temp[i] = songs[i];
        }
        temp[i] = newSong;
        for (; i < numSongs; i++) {
            temp[i + 1] = songs[i];
        }
    }
    numSongs++;
    delete[] songs;
    songs = temp;
}

/// @brief removes a song from the library by index
/// @param indexToRemove
void SongLibrary::performRemoveSong(int indexToRemove) {
    Song rem = songs[indexToRemove];
    if (indexToRemove < 0 || indexToRemove >= numSongs) {
        cout << "Invalid index\n";
        return;
    }
    Song *temp = new Song[numSongs - 1];
    int i = 0;
    numSongs--;
    for (; i < indexToRemove; i++) {
        temp[i] = songs[i];
    }
    for (; i < numSongs; i++) {
        temp[i] = songs[i + 1];
    }
    delete[] songs;
    songs = temp;

    cout << "\nRemoved song:\n\t";
    rem.displaySong();
    cout << '\n';
}

/// @brief edits a song in the library by index
/// @param indexToEdit
/// @param att attribute to edit
/// @param newAttributeValue new attribute value
void SongLibrary::performEditSong(int indexToEdit, SongAttribute att, string newAttributeValue) {
    string old = songs[indexToEdit].getAttribute(att);
    songs[indexToEdit].setAttribute(att, newAttributeValue);
    if (att == sortAtt) this->performSort(att); //ensure array stays sorted
    cout << "\nEdited song " << indexToEdit+1 << ":\n\t" << SongAttributeStrings[att] << " changed from " << old << " to " << newAttributeValue << "\n";
}