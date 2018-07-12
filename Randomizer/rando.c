#include "rando.h"

int main(int argc, char *argv[]) {

	srand(time(NULL));

	if(argc == 2){
		printf("Proper Usage: ./Randomizer\n");
		exit(EXIT_FAILURE);
	} else {
		printf("Welcome!\n");
	}

	menu();

	return 0;
}
