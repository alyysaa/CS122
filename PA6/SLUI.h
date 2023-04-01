#ifndef SLUI_H
#define SLUI_H

//Song Library User Interface (SLUI)

#include "SongLibrary.h"

using namespace std;

const int FIRST_OPTION = 1;
const int LAST_OPTION = 9;

void stripNewlines(string *);
void displayMenu();
int getOption();
void exeChoice(int, SongLibrary &);
void runMusic(int, char*[]);

void testCopy();

#endif