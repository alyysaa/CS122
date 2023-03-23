#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <iostream>
#include <fstream>
#include "Song.h"

using namespace std;



class SongLibrary
{
private:
    int numSongs;
    Song *songs;

    SongAttribute sortAtt;
    void computeMaxLengths(int *, int *, int *, int *);

public:
    SongLibrary();
    SongLibrary(int, Song *);
    SongLibrary(int, Song *, SongAttribute);

    ~SongLibrary();

    int getNumSongs();
    Song *getSongsArray();

    void displayLibrary();

    void performLoad(string);
    void performSave(string);
    void performSort(SongAttribute);
    bool performSearch(SongAttribute, string, Song *, int *);

    void performAddSong(Song);
    void performRemoveSong(int);
    void performEditSong(int, SongAttribute, string);

};

#endif