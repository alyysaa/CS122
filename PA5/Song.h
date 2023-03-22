#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <iomanip>

using namespace std;

const int MIN_RATING = 1;
const int MAX_RATING = 5;

string convertToLowercase(const string);
void formattedCout(const string, const int);

enum SongAttribute { TITLE, ARTIST, GENRE, RATING, NIL };
const string SongAttributeStrings[] = { "title", "artist", "genre", "rating" };

SongAttribute stringToSongAttribute(const string s);

class Song
{
private:
    string title;
    string artist;
    string genre;
    int rating;
public:

    Song();
    Song(const string, const string, const string, const int);

    void setAttribute(SongAttribute, string);
    string getAttribute(SongAttribute);
    int getRating();

    void displaySong();
    void formattedDisplay(int, int, int, int);

};

#endif