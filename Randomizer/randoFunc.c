#include "rando.h"

void menu(){

	char buffer[3];
	int userOpt;

	printf("SUPER EPIC PROGRAM OF RANDOMNESS!\n\n");
	printf("(1) Dice Roller\n");
	printf("(2) Area of a Circle\n");
	printf("(3) Volume of a Cube\n");
	printf("(4) Hi/Lo Game\n");
	printf("(0) Quit\n\n");
	printf("Please make a selection: ");


	if(fgets(buffer, 3, stdin) != NULL){
		if(validate(buffer, 1, 0)){
			userOpt = buffer[0];
			switch(userOpt)
				{
				case DICE_ROLLER:
					dice();
					break;
				case CIRCLE_AREA:
					circle();
					break;
				case CUBE_VOLUME:
					cube();
					break;
				case HI_LO:
					hiLo();
					break;
				case QUIT:
					printf("\n\nExiting Program..\n");
					exit(EXIT_SUCCESS);
				default:
					printf("\nAn invalid option has been selected. Please try again.\n");
					menu();
				}
		} else {
			printf("Please try again.\n");
			menu();
		}
	} else {
		printf("Error reading input. Please try again.\n");
		menu();
	}
}
void dice(){

	long numDice, numSides, numRolls;
	char *endPtr1, *endPtr2, *endPtr3;
	char input[5];
	printf("\n\n\n-----Dice Roller-----\n\n\n");
	printf("How many dice [1-9999]: ");
	if(fgets(input, 6, stdin) != NULL){
		if(validate(input, 4, 0)){
			numDice = strtol(input, &endPtr1, 10);
			printf("How many sides [1-9999]: ");
			if(fgets(input, 6, stdin) != NULL){
				if(validate(input, 4, 0)){
					numSides = strtol(input, &endPtr2, 10);
					printf("How many rolls [1-9999]: ");
					if(fgets(input, 6, stdin) != NULL){
						if(validate(input, 4, 0)){
							numRolls = strtol(input, &endPtr3, 10);
						} else {error(); dice();}
					}
				} else {error(); dice();}
			}
		} else {error(); dice();}
	} else {
		error();
		dice();
	}
	printf("Dice: %ld\nSides: %ld\nRolls: %ld\n\n", numDice, numSides, numRolls);
	for(int i = 0; i < numRolls; i++){
		printf("----------Roll #%d----------\n", i+1);
		for(int j = 0; j < numDice; j++){
			printf("%d ", rand() % (int)numSides + 1);
		}
		printf("\n");
	}
	printf("\n\n\n");
	clean();
	menu();
}
void circle(){
	//TODO: Add ability to write to file

	char input[25];
	int selection;
	float calc;
	char *endPtr;

	printf("\n\n\n-----Area of a Circle-----\n\n\n");
	printf("Which of the following do you know:\n"
			"(1)\tRadius\n(2)\tDiameter\n(3)\tCircumference\n");
	printf("Selection: ");
	if(fgets(input, 3, stdin) != NULL){
		if(validate(input, 1, 0)){
			selection = input[0];
			switch(selection)
			{
			case '1':
				printf("Enter the Radius [20 digits max]: ");
				if(fgets(input, 23, stdin) != NULL){
					if(validate(input, 20, 1)){
						calc = strtof(input, &endPtr);
						printf("The area of your circle with Radius %f is:\n", calc);
						printf("%f\n\n", M_PI * (powf(calc, 2)));
					} else {error(); circle();}
				} else {error(); circle();}
				break;
			case '2':
				printf("Enter the Diameter [20 digits max]: ");
				if(fgets(input, 23, stdin) != NULL){
					if(validate(input, 20, 1)){
						calc = strtof(input, &endPtr);
						printf("The area of your circle with Diameter %f is:\n", calc);
						printf("%f\n\n", (M_PI/4) * (powf(calc,2)));
					} else {error(); circle();}
				} else {error(); circle();}
				break;
			case '3':
				printf("Enter the Circumference [20 digits max]: ");
				if(fgets(input, 23, stdin) != NULL){
					if(validate(input, 20, 1)){
						calc = strtof(input, &endPtr);
						printf("The area of your circle with Circumference %f is:\n", calc);
						printf("%f\n\n", powf(calc,2)/(4*M_PI));
					} else {error(); circle();}
				} else {error(); circle();}
				break;
			}
		} else {error(); circle();}
	} else {error(); circle();}
	clean();
	menu();
}
void cube(){
	printf("cube\n");
	menu();
}
void hiLo(){
	printf("hilo\n");
	menu();
}

void clean(){
	char trash;
	int flags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, O_NONBLOCK);
	if(!feof(stdin)){
		do trash=getchar(); while(trash != '\n' && trash != EOF);
	}
	fcntl(0, F_SETFL, flags);
}

int validate(char *input, int buf, int isFloatAllowed){
	for(int i = 0; i <= buf; i++){
				if(input[i] == '\n' || input[i] == EOF || input[i] == '\0'){
					if(i == 0){
						printf("Input empty.\n");
						return 0;
					} else {
						i = buf+1;
					}
				}
				else if(!isdigit(input[i]) && input[i] != '\n' && input[i] != EOF){
					if(input[i] == '.' && isFloatAllowed == 1){
						break;
					} else {
						printf("Input was not a number.\n");
						clean();
						return 0;
					}
				}
				else if(i == buf){
					printf("Your input was too long.\n");
					clean();
					return 0;
				}
			}
	clean();
	return 1;
}

void error(){
	printf("Error reading input. Please try again.\n");
	clean();
}
