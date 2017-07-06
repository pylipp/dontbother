/* ESSENTIAL GAME CONSTANTS
 * change in order to set
 * - number of players (1 < PLAYERS < 27)
 * - number of pieces per player (>0)
 * - distance between two players' start fields (>= PIECES)
 * - (implicitely) total number of fields
 * - largest pip to be rolled with dice
 * - number of (re-)tries when having no piece on the field
 * VERBOSE is a preprocessor flag and has to passed 
 * at compiling with -DVERBOSE=<0/1>
 */
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

const int PLAYERS = 4;
const int PIECES = 4;
const int INBETWEEN = 10;
const int FIELDS = PLAYERS*INBETWEEN;
const int MAXPIPS = 6;
const int MAXTRIES = 3;
//const bool VERBOSE = false;

#endif 
