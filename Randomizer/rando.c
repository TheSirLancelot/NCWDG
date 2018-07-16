#include "rando.h"

int main(int argc, char *argv[]) {
    
    //Seed for rand()
	srand(time(NULL));

    //Display proper usage to user
	if(argc == 2){
		printf("Proper Usage: ./Randomizer\n");
		exit(EXIT_FAILURE);
	} else {
		printf("Welcome!\n");
	}

    //Initialize program
	menu();

	return 0;
}
