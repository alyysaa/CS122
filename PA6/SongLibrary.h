#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <fstream>
#include "Song.h"

using namespace std;



class SongLibrary
{
private:

    Song *head;
    Song *tail;
    SongAttribute sortAtt;

    bool isReversed;

    void computeMaxLengths(int *, int *, int *, int *);

    // only used by performLoad and copy constructor in some cases
    void appendSong(Song *);

    string getSortableAttribute(Song*, SongAttribute); // gets lowercase form of attribute

    void performRatingInsert(Song *);

    void reverseList();


    void clear();

public:

    SongLibrary();

    SongLibrary(const SongLibrary &);

    ~SongLibrary();

    void setHead(Song *);

    void performLoad(string);

    void performSave(string);

    void performSort();

    // assignment requires a setter for sortAtt
    // this acts as such, since the library should always be sorted
    void performSort(SongAttribute);

    SongAttribute getSortAtt();

    string isReversedString();

    Song *performSearch(SongAttribute, const string, bool *, int *);

    void performInsertSongInOrder(Song *);

    void performRemoveSong(Song *);

    void performEditSong(Song *, SongAttribute, string);

    void displayLibrary();

};

#endif