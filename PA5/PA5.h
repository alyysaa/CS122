#ifndef PA5_H
#define PA5_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Song.h"
#include "SongLibrary.h"

using namespace std;

const int FIRST_OPTION = 1;
const int LAST_OPTION = 9;
const int QUIT_OPTION = 9;

void displayMenu();
int getValidChoice();
void executeUserChoice(int, SongLibrary&);
void runMusicManager();

#endif