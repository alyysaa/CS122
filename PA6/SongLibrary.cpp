#include "SongLibrary.h"

/// @brief computes the maximum length of each attribute in the library
/// @param titleW title width
/// @param artistW artist width
/// @param genreW genre width
/// @param ratingW rating width (technically not necessary because all ratings in this case will be between 1 and 5)
void SongLibrary::computeMaxLengths(int *titleW, int *artistW, int *genreW, int *ratingW) {
    const int OFFSET = 3; //offset for spacing all items
    Song *cur = head;
    while (cur != NULL) {
        if (cur->getAttribute(TITLE).length() > *titleW) *titleW = cur->getAttribute(TITLE).length();
        if (cur->getAttribute(ARTIST).length() > *artistW) *artistW = cur->getAttribute(ARTIST).length();
        if (cur->getAttribute(GENRE).length() > *genreW) *genreW = cur->getAttribute(GENRE).length();

        //technically not necessary because all ratings in this case will be between
        if (to_string(cur->getRating()).length() > *ratingW) *ratingW = to_string(cur->getRating()).length();

        cur = cur->getNext();
    }
    //allow spacing between each column
    *titleW += OFFSET;
    *artistW += OFFSET;
    *genreW += OFFSET;
    *ratingW += OFFSET;
}

/// @brief append a song to the end of the list, used by performLoad and copy constructor. Note no error checking is done.
/// @param s song to append
void SongLibrary::appendSong(Song *s) {
    if (head == NULL) {
        head = tail = s;
        return;
    }
    tail->setNext(s);
    s->setPrev(tail);
    tail = s;
}

/// @brief gets an attribute from a song and converts it to lowercase, used to simplify calls when sorting
/// @param s song to get attribute from
/// @param att attribute to get
/// @return s->getAttribute(att) converted to lowercase
string SongLibrary::getSortableAttribute(Song *s, SongAttribute att) {
    if (s == NULL) {
        cout << "Error: Song is NULL.\n";
        return NULL;
    }
    return convertToLowercase(s->getAttribute(att));
}

/// @brief clears the library, used by destructor and copy constructor
void SongLibrary::clear() {
    if (head == NULL) return;
    if (head == tail) {
        delete head;
        head = tail = NULL;
        return;
    }
    Song *cur = head;
    Song *temp = cur->getNext();
    while (cur != NULL) {
        delete cur;
        cur = temp;
        temp = cur->getNext();
    }
    head = tail = NULL;
}

/// @brief default constructor, sets head and tail to NULL and sort attribute to TITLE
SongLibrary::SongLibrary() {
    head = NULL;
    tail = NULL;
    isReversed = false;
    sortAtt = TITLE;
}

/// @brief (deep) copy constructor, used to copy a library. Note this is unused in the assignment requirements, but it does work. 
///        Uncomment the line in main.cpp to test it.
/// @param other library to copy from
SongLibrary::SongLibrary(const SongLibrary &other) {
    isReversed = other.isReversed;
    sortAtt = other.sortAtt;
    Song *temp;
    if (other.head != NULL) {
        int songCount = 0;
        temp = other.head;
        while (temp != NULL) {
            this->appendSong(new Song(*temp));
            songCount++;
            temp = temp->getNext();
        }
        cout << "Loaded " << songCount << " songs.\n";
    }
    else { head = tail = NULL; }
}

/// @brief destructor, calls clear()
SongLibrary::~SongLibrary() {
    this->clear();
}

/// @brief clears list and sets the new head of list. Unused in this implementation, included per assignment requirements
/// @param s new head of list
void SongLibrary::setHead(Song *s) {
    if (head != NULL) clear();
    if (s == NULL) return;

    this->head = s;
    Song *cur = head;

    while (cur->getNext() != NULL) cur = cur->getNext();

    this->tail = cur;
}

/// @brief loads a library from a file
/// @param filename file to load from
void SongLibrary::performLoad(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }

    string title, artist, genre, rating;
    int numSongs = 0;

    while (!file.eof()) {
        title = artist = genre = rating = "";

        getline(file, title);
        getline(file, artist);
        getline(file, genre);
        getline(file, rating);
        numSongs++;

        if (title == "" || artist == "" || genre == "" || rating == "") {
            cout << "Invalid file format, load failed at song " << numSongs << ".\n";
            return;
        }

        int ratingInt;
        try {
            ratingInt = stoi(rating);
        }
        catch (const std::exception &e) {
            cout << "Inavlid rating format on song " << numSongs << ". Setting rating to minimum ("
                << MIN_RATING << ").\n";
            ratingInt = MIN_RATING;
        }

        this->performInsertSongInOrder(new Song(title, artist, genre, ratingInt));

        getline(file, title); //skip the newline
    }
}

/// @brief saves library to a file
/// @param filename file to save to
void SongLibrary::performSave(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }
    Song *cur = head;
    while (cur != NULL) {
        file << cur->getAttribute(TITLE) << endl;
        file << cur->getAttribute(ARTIST) << endl;
        file << cur->getAttribute(GENRE) << endl;
        file << cur->getRating();
        cur = cur->getNext();
        if (cur != NULL) file << endl << endl;
    }
    file.close();
    cout << "Saved to file " << filename << endl;
}

/// @brief sorts librarry by sort attribute
void SongLibrary::performSort() {
    Song *cur = head;
    head = tail = NULL;
    while (cur != NULL) {
        Song *temp = cur->getNext();
        this->performInsertSongInOrder(cur);
        cur = temp;
    }
}

/// @brief SLUI used function, changes sort attribute and reverses list if already sorted by that attribute
/// @param sortAtt attribute to sort by
void SongLibrary::performSort(SongAttribute sortAtt) {
    if (this->sortAtt == sortAtt){
        this->isReversed = !isReversed;
        return this->reverseList();
    }
    this->isReversed = false;
    this->sortAtt = sortAtt;
    this->performSort();
}

/// @brief reverse the list, used by performSort(SongAttribute) when sorting by the same attribute twice
void SongLibrary::reverseList(){
    Song *cur = head;
    Song *temp;
    while (cur != NULL) {
        temp = cur->getNext();
        cur->setNext(cur->getPrev());
        cur->setPrev(temp);
        cur = temp;
    }
    temp = head;
    head = tail;
    tail = temp;
}

/// @brief assignment required function, unused in this implementation
/// @return this->sortAtt
SongAttribute SongLibrary::getSortAtt() {
    return sortAtt;
}

/// @brief searches for a song by attribute and value
/// @param att attribute to search by
/// @param value value to search for
/// @param found pointer to bool to set to true if found, false otherwise
/// @param index pointer to int to set to index of song if found, -1 otherwise
/// @return song if found, NULL otherwise
Song *SongLibrary::performSearch(SongAttribute att, const string value, bool *found, int *index) {
    if (att == NIL) {
        cout << "Error: Invalid attribute.\n";
    }
    string val = convertToLowercase(value);
    if (head == tail) {
        if (head == NULL || getSortableAttribute(head, att) != val) {
            *found = false;
            *index = -1;
            return NULL;
        }
        // getSortableAttribute(head) == val, so we found it
        *found = true;
        *index = 0;
        return head;
    }

    Song *cur = head;
    int i = 0;
    while (cur != NULL) {
        if (getSortableAttribute(cur, att) == val) {
            *found = true;
            *index = i;
            return cur;
        }
        cur = cur->getNext();
        i++;
    }

    *found = false;
    *index = -1;
    return NULL;

}

/// @brief inserts a song into the list in order (based on sort attribute)
/// @param s song to insert
void SongLibrary::performInsertSongInOrder(Song *s) {
    //cases when this song is already in the list, most commonly from a sort
    if (s->getNext() != NULL) {
        s->getNext()->setPrev(s->getPrev());
    }
    if (s->getPrev() != NULL) {
        s->getPrev()->setNext(s->getNext());
    }
    s->setNext(NULL);
    s->setPrev(NULL);

    if (head == NULL) {
        head = tail = s;
        return;
    }

    if (sortAtt == RATING){
        return this->performRatingInsert(s);
    }

    if (getSortableAttribute(s, sortAtt) > getSortableAttribute(tail, sortAtt)) return appendSong(s);

    Song *cur = head;

    //songs with the same value will be sorted in this case based on the order they were added
    //swaps are possible if the list is sorted in specific ways
    while (cur->getNext() != NULL && getSortableAttribute(s, sortAtt) >= getSortableAttribute(cur, sortAtt)) {
        cur = cur->getNext();
    }

    if (cur == head) {
        s->setNext(head);
        head->setPrev(s);
        head = s;
        return;
    }

    s->setNext(cur);
    s->setPrev(cur->getPrev());
    cur->getPrev()->setNext(s);
    cur->setPrev(s);


}

/// @brief inserts a song into the list in order based on rating, because ratings are sorted in reverse order by default
/// @param s song to insert
void SongLibrary::performRatingInsert(Song *s){
    if (s->getRating() <= tail->getRating()) return appendSong(s);

    Song *cur = head;
    while (cur->getNext()!=NULL && s->getRating() < cur->getRating()){
        cur = cur->getNext();
    }

    if (cur == head){
        s->setNext(head);
        head->setPrev(s);
        head = s;
        return;
    }

    s->setNext(cur);
    s->setPrev(cur->getPrev());
    cur->getPrev()->setNext(s);
    cur->setPrev(s);
}

/// @brief removes a song from the list, updating relevant pointers
/// @param s song to remove
void SongLibrary::performRemoveSong(Song *s) {
    if (s == head) {
        head = head->getNext();
        if (head != NULL) head->setPrev(NULL);
        else tail = NULL;
        delete s;
        return;
    }
    if (s == tail) {
        tail = tail->getPrev();
        if (tail != NULL) tail->setNext(NULL);
        else head = NULL;
        delete s;
        return;
    }

    s->getPrev()->setNext(s->getNext());
    s->getNext()->setPrev(s->getPrev());
    delete s;
}

/// @brief edits one attribute of a song in the library, updates its position in the list if necessary
/// @param s song to edit
/// @param att attribute to edit
/// @param val new value for attribute
void SongLibrary::performEditSong(Song *s, SongAttribute att, string val) {
    s->setAttribute(att, val);
    if (att == sortAtt) {
        this->performInsertSongInOrder(s);
    }
}

/// @brief displays the library in a formatted table, calls Song::formattedDisplay() and SongLibrary::computeMaxLengths()
void SongLibrary::displayLibrary() {
    if (head == NULL) {
        cout << "Library is empty.\n";
        return;
    }
    int titleW = 6; //"Title "
    int artistW = 7; //"Artist "
    int genreW = 6; //"Genre "
    int ratingW = 7; //"Rating "
    computeMaxLengths(&titleW, &artistW, &genreW, &ratingW);
    cout << "Library " << this->isReversedString() << "sorted by - " << SongAttributeStrings[sortAtt] << endl;
    formattedCout("Title", titleW);
    formattedCout("Artist", artistW);
    formattedCout("Genre", genreW);
    formattedCout("Rating", ratingW);
    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    Song *cur = head;
    while (cur != NULL) {
        cur->formattedDisplay(titleW, artistW, genreW, ratingW);
        cur = cur->getNext();
    }
    cout << "---------------------------------------------------------------------------" << endl;



}


/// @return "reverse " if this->isReversed is true, "" otherwise
string SongLibrary::isReversedString(){
    return this->isReversed ? "reverse " : "";
}