#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#ifndef RANDO_H_
#define RANDO_H_


#define BUF 40
#define DICE_ROLLER 49
#define CIRCLE_AREA 50
#define CUBE_VOLUME 51
#define HI_LO 52
#define QUIT 48



void menu();
void dice();
void circle();
void cube();
void hiLo();
void clean();
int validate(char *input, int buf, int isFloatAllowed);
void error();

#endif /* RANDO_H_ */
