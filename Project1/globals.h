//
//  globals.h
//  project1
//
//  Created by Megha Ilango on 1/13/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//

#ifndef globals_h
#define globals_h

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 100;         // max number of Flatulans allowed
const int INITIAL_PLAYER_HEALTH = 10;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;
const int HISTORY = 5;

int randInt(int min, int max);
void clearScreen();

#endif /* globals_h */
