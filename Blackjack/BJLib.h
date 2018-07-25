#ifndef BJLIB_H_
#define BJLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> //for printing symbols
#include <locale.h> //also for printing symbols
#include <string.h> //string manipulation
#include <unistd.h> //for sleep function

//struct declaration
typedef struct card Card;
typedef struct player Player;

//global vars
extern const wchar_t SPADE;
extern const wchar_t HEART;
extern const wchar_t DIAMOND;
extern const wchar_t CLUB;

//function prototypes
void menu();
void game();
void rules();
void cleanup();
Player *newPlayer(char *name);

//TODO: THESE FUNCTIONS
void deal();
void hit();

#endif
