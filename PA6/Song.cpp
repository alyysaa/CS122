#include "Song.h"



/// @brief returns the string in lowercase, required by PA5 specifications
/// @param s string to convert
/// @return s in lowercase
string convertToLowercase(const string s) {
    string r;
    for (int i = 0; i < s.length(); i++) {
        r += tolower(s[i]);
    }
    return r;
}

/// @brief formats the output of a string to a specified width
/// @param s text to format
/// @param w width
void formattedCout(const string s, const int w) {
    cout << left << setw(w) << s;
}

/// @brief returns the value of the attribute specified by the parameter
/// @param s string to convert
/// @return the corresponding SongAttribute, NIL if invalid
SongAttribute stringToSongAttribute(const string s) {
    string s2 = convertToLowercase(s);
    for (int i = 0; i < 4; i++) {
        if (s2 == SongAttributeStrings[i]) {
            return (SongAttribute)i;
        }
    }
    return NIL;
}

/// @brief private method for changing rating, the only attribute that has limits on its input
/// @param rating new rating for the song
void Song::setRating(int rating) {
    if (rating < MIN_RATING || rating > MAX_RATING) {
        cout << "Rating must be in [" << MIN_RATING << ", " << MAX_RATING << "]\n";
    }
    if (rating < MIN_RATING) {
        this->rating = MIN_RATING;
        cout << "Rating set to " << MIN_RATING << '\n';
    }
    else if (rating > MAX_RATING) {
        this->rating = MAX_RATING;
        cout << "Rating set to " << MAX_RATING << '\n';
    }
    else {
        this->rating = rating;
    }
}


/// @brief default constructor for Song class
Song::Song() {
    title = "";
    artist = "";
    genre = "";
    rating = MIN_RATING;
    next = prev = NULL;
}

/// @brief explicit constructor for Song class
/// @param title title of song
/// @param artist song artist
/// @param genre song genre
/// @param rating song rating (must be in [MIN_RATING, MAX_RATING])
Song::Song(const string title, const string artist, const string genre, const int rating) {
    this->title = title;
    this->artist = artist;
    this->genre = genre;

    //rating is the only attribute that needs to be validated
    this->setRating(rating);
}

/// @brief deep copy constructor for Song class
/// @param s song to copy
Song::Song(const Song &s) {
    title = s.title;
    artist = s.artist;
    genre = s.genre;
    rating = s.rating;
    next = NULL; //assignment requires that next and prev be set to NULL
    prev = NULL; //assignment requires that next and prev be set to NULL
}

/// @return this->next
Song *Song::getNext() {
    return this->next;
}

/// @brief sets Song.next pointer to new value, returns old value
/// @param n new Song.next pointer
/// @return old Song.next pointer
Song *Song::setNext(Song *n) {
    Song *oldNext = this->next;
    this->next = n;
    return oldNext;
}

/// @return this->prev
Song *Song::getPrev() {
    return this->prev;
}

/// @brief sets Song.prev pointer to new value, returns old value
/// @param p new Song.prev pointer
/// @return old Song.prev pointer
Song *Song::setPrev(Song *p) {
    Song *oldPrev = this->prev;
    this->prev = p;
    return oldPrev;
}

/// @brief sets attribute specified to new value
/// @param attribute song atttribute to be altered
/// @param value new value
void Song::setAttribute(SongAttribute attribute, string value) {
    switch (attribute) {
    case TITLE:
        title = value;
        break;
    case ARTIST:
        artist = value;
        break;
    case GENRE:
        genre = value;
        break;
    case RATING: {
        setRating(stoi(value));

    }   break;
    default:
        cout << "Invalid attribute: " << attribute << '\n';
    }
}

/// @brief displays song in the format "title by artist (genre, rating)"
void Song::displaySong() {
    cout << title << " - " << artist << " (" << genre << ", " << rating << "/" << MAX_RATING << ")\n";
}

/// @brief outputs the song in a formatted way
/// @param tw title width
/// @param aw artist width
/// @param gw genre width
/// @param rw rating width
void Song::formattedDisplay(int tw, int aw, int gw, int rw) {
    formattedCout(this->title, tw);
    formattedCout(this->artist, aw);
    formattedCout(this->genre, gw);
    formattedCout(to_string(this->rating), rw);
    cout << endl;
}

/// @brief returns the rating of the song, essentially the same as stoi(getAttribute(RATING))
int Song::getRating() {
    return rating;
}

/// @brief get a specified attribute from the song
/// @param att attribute to get
/// @return string value of attribute
string Song::getAttribute(SongAttribute att) {
    switch (att) {
    case TITLE:
        return title;
    case ARTIST:
        return artist;
    case GENRE:
        return genre;
    case RATING:
        return to_string(rating);
    case NIL:
        cout << "Invalid attribute: " << att << '\n';
        return NULL;
    }
}

