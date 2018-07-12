#include <stdio.h>
#include <stdlib.h>
#ifndef PROGRAM_H_
#define PROGRAM_H_

#define BUFSIZE 100

struct point
{
	int x;
	int y;
};

struct shape
{
	struct point edge1;
	struct point edge2;
	struct point edge3;
	struct point edge4;
};

int readInput(char *buf, int size, int *bytesRead);
void *welcomeMessage();
void exitProgram(int exitVal);
void createRectangle(struct shape *rectangle);
struct point createPoint(int x, int y);
int calcArea(struct shape *rectangle);

#endif /* PROGRAM_H_ */
