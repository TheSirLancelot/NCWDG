#include "program.h"

int main(int argc, char *argv[]) {

	int charsRead;
	int returnVal = 0;
	char buf[BUFSIZE] = {0};
	struct shape rectangle = {0};

	if(argc == 2){
		printf("%s\n", argv[1]);
	}
	else{
		printf("%s\n", (char *)welcomeMessage());
	}

	returnVal = readInput(buf, sizeof(buf), &charsRead);

	if(!returnVal){
		exitProgram(EXIT_FAILURE);
	}

	printf("%s\n", buf);
	printf("The function read in %d characters\n", charsRead);

	createRectangle(&rectangle);

	printf("Area of rectangle is %d\n", calcArea(&rectangle));

	exitProgram(EXIT_SUCCESS);

}

int readInput(char *buf, int size, int *bytesRead){
	int counter = 0;
	int nextChar = 0;
	int bufSize = sizeof(buf);

	for(counter = 0; counter < size - 1; counter++){
		nextChar = getchar();
		if(nextChar == EOF){
			return 0;
		}

		*buf = nextChar;
		buf++;

		if(nextChar == '\n'){
			break;
		}
	}

	*bytesRead = counter + 1;
	*buf = '\0';

	return 1;
}

void *welcomeMessage(){
	return "Welcome to the program";
}

void exitProgram(int exitVal){
	exit(exitVal);
}

struct point createPoint(int x, int y){
	struct point p = {0};
	p.x = x;
	p.y = y;
	return p;
}

void createRectangle(struct shape *rectangle){
	rectangle->edge1 = createPoint(0,0);
	rectangle->edge2 = createPoint(10,0);
	rectangle->edge3 = createPoint(10,5);
	rectangle->edge4 = createPoint(0,5);
}

int calcArea(struct shape *rectangle){
	return (rectangle->edge2.x - rectangle->edge1.x) * (rectangle->edge3.y - rectangle->edge2.y);
}

