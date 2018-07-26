#ifndef BJLIB_H_
#define BJLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> //for printing symbols
#include <locale.h> //also for printing symbols
#include <string.h> //string manipulation
#include <unistd.h> //for sleep function
#include <time.h> //used to get a seed for rand()
#include <fcntl.h> //for clean()

//struct declaration
typedef struct card Card;
typedef struct player Player;

//symbols for suits
const wchar_t SPADE = 0x2664;
const wchar_t HEART = 0x2661;
const wchar_t DIAMOND = 0x2662;
const wchar_t CLUB = 0x2667;
//keeping track of number of games
int gameNum = 0;
char *name = NULL; //holds player name

//function prototypes
void menu();
void game();
void rules();
Player *newPlayer(char *name);
void show(Player *p, int numCards, int hasHole);
void score(Player *p, int hasHole);
void playAgain(Player *p, Player *d);

#endif
