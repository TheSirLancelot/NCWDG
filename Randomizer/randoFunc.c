#include "rando.h"

void menu(){

    //Local Variables
	char buffer[3];
	int userOpt;

    //Menu Options
	printf("SUPER EPIC PROGRAM OF RANDOMNESS!\n\n");
	printf("(1) Dice Roller\n");
	printf("(2) Area of a Circle\n");
	printf("(3) Volume of a Cube\n");
	printf("(4) Hi/Lo Game\n");
	printf("(0) Quit\n\n");
	printf("Please make a selection: ");

    //Set buffer to 3 to accomodate newline and null terminator
	if(fgets(buffer, 3, stdin) != NULL){
        //Validate 1 char of buffer, no floats allowed
		if(validate(buffer, 1, 0)){
            //First char of array (should be the only character) is user Option
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

    //Local Variables
	long numDice, numSides, numRolls;
	char *endPtr1, *endPtr2, *endPtr3;
	char input[6];

    //Get user input for 3 options. Buffer = 6; Validating 4 chars (max input of 9999)
	printf("\n\n\n-----Dice Roller-----\n\n\n");
	printf("How many dice [1-9999]: ");
	if(fgets(input, 6, stdin) != NULL){
		if(validate(input, 4, 0)){
            numDice = strtol(input, &endPtr1, 10);
            if(numDice == 0){error(); dice();}
            printf("How many sides [1-9999]: ");
	    	if(fgets(input, 6, stdin) != NULL){
	    		if(validate(input, 4, 0)){
		    		numSides = strtol(input, &endPtr2, 10);
                    if(numSides == 0){error(); dice();}
                    printf("How many rolls [1-9999]: ");
					if(fgets(input, 6, stdin) != NULL){
				    	if(validate(input, 4, 0)){
                            numRolls = strtol(input, &endPtr3, 10);
                            if(numRolls == 0){error(); dice();}
						} else {error(); dice();}
					} else {error(); dice();}
				} else {error(); dice();}
			} else {error(); dice();}
		} else {error(); dice();}
	} else { error(); dice();}

    //Printing calculations using user input from above
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

    //Local Variables
	char input[25];
	int selection;
	float calc;
	char *endPtr;

    //Get user input depending on what user knows (radius, diameter, circumference)
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
						printf("%f\n\n", M_PI * (powf(calc, 2))); //Area=PI*R^2
                        saveFile(1,calc,0); //Asks if user wants to save;
					} else {error(); circle();}
				} else {error(); circle();}
				break;
			case '2':
				printf("Enter the Diameter [20 digits max]: ");
				if(fgets(input, 23, stdin) != NULL){
					if(validate(input, 20, 1)){
						calc = strtof(input, &endPtr);
						printf("The area of your circle with Diameter %f is:\n", calc);
						printf("%f\n\n", (M_PI/4) * (powf(calc,2))); //Area=(PI/4)*(D^2)
                        saveFile(2,calc,0);
					} else {error(); circle();}
				} else {error(); circle();}
				break;
			case '3':
				printf("Enter the Circumference [20 digits max]: ");
				if(fgets(input, 23, stdin) != NULL){
					if(validate(input, 20, 1)){
						calc = strtof(input, &endPtr);
						printf("The area of your circle with Circumference %f is:\n", calc);
						printf("%f\n\n", powf(calc,2)/(4*M_PI)); //Area=(C^2)/(4*PI)
                        saveFile(3,calc,0);
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

    //Local Variables
    char input[9];
    char *endptr;

    //Get length of cube side
	printf("\n\n\n-----Volume of a Cube-----\n\n\n");
    printf("Enter the length of 1 side [1-2642245]:\n");
    if(fgets(input, 9, stdin) != NULL){
        if(validate(input, 7, 0)){
            //Using unsigned long long to accomodate very large number
            unsigned long long out = strtol(input, &endptr, 10); 
            if(out>2642245){ //This is the maximum number that can be cubed w/in bounds of %llu
                printf("Your number is too large. Please try again.\n");
                clean();
                menu();
            } else {
                printf("The volume of your cube is: %llu\n\n", (out*out*out)); //Volume=L^3
                saveFile(4,0,out);
            }
        } else {error(); cube();}
    } else {error(); cube();}
    clean();
    menu();
}
void hiLo(){

    //Local Variables
    int number = rand() % 100 + 1; //Gens new random number each time game is played
    char input[5];
    char *endPtr;
    long guess;
    int tries = 5;

    //User gets 5 tries to guess number; Only valid guesses count
	printf("Guess the number [1-100]. You only get 5 tries! (Invalid input doesn't count against you)\n");
    while(tries > 0){
        if(fgets(input, 5, stdin) != NULL){
            if(validate(input, 3, 0)){
                guess = strtol(input, &endPtr, 10);
                if(guess == number){
                    printf("Congratulations! You guessed correctly with %d guesses left!\n\n", tries);
                    break;
                } else if (guess > number){
                    tries--;
                    printf("Lower..\nNum guesses remaining: %d\n", tries);
                } else if (guess < number){
                    tries--;
                    printf("Higher..\nNum guesses remaining: %d\n", tries);
                }
            } else {error();}
        } else {error();}
    }
    if(tries == 0){
        printf("Womp womp.. Better luck next time. The answer was %d\n\n", number);
    }
    clean();
	menu();
}

//Func to clean stdin after user input
void clean(){

    //Local Variables
	char trash;
	int flags = fcntl(0, F_GETFL); //Get backup of current stdin flags

	fcntl(0, F_SETFL, O_NONBLOCK); //Set stdin to non-blocking
	if(!feof(stdin)){ //Grab char THEN check if newline or EOF
		do trash=getchar(); while(trash != '\n' && trash != EOF);
	}
	fcntl(0, F_SETFL, flags); //Revert stdin flags to backup
    trash = 0;
}

/*
 * Func to validate user input given a pointer to the input, 
 * the size wanted, and whether or not floats are allowed (for the circle)
*/
int validate(char *input, int buf, int isFloatAllowed){
	for(int i = 0; i <= buf; i++){
                //is char newline, EOF, or null terminator
				if(input[i] == '\n' || input[i] == EOF || input[i] == '\0'){
                    //If so, and at beginning of input, input is empty
					if(i == 0){
						printf("Input empty.\n");
						return 0;
					} else { //Increase the buffer
						i = buf+1;
					}
				}
                //is char a digit and not newline or EOF
				else if(!isdigit(input[i]) && input[i] != '\n' && input[i] != EOF){
                    //Can be a decimal as long as floats are allowed
					if(input[i] == '.' && isFloatAllowed == 1){
						break;
					} else {
						printf("Input was not a number.\n");
						clean();
						return 0;
					}
				}
                //is buffer greater than the num of chars wanted
				else if(i == buf){
					printf("Your input was too long.\n");
					clean();
					return 0;
				}
			}
	clean();
	return 1;
}

//We print errors alot around here, might as well make a function for it..
void error(){
	printf("Error reading input. Please try again.\n");
	clean();
}

/*
 * Func to save to a file. Accepts choice for print statement,
 * float for circle, and a llu for a cube.
 */
void saveFile(int choice, float circle, unsigned long long cube){
    
    //Local Variables
    char buffer[3];
    int userOpt;
    char *endPtr;
    FILE *file;

    printf("Would you like to save this result to a file? (./results.txt)\n1) Yes\n2) No\nSelection: ");
    if(fgets(buffer, 3, stdin) != NULL){
        if(validate(buffer, 1, 0)){
            userOpt = buffer[0];
            if(userOpt == '1'){
                file = fopen("results.txt", "a"); //Opens text file in current directory
                if(file == NULL){ //if fopen fails
                    perror("Error: "); //print the error
                    return;
                } else {
                    switch(choice)
                    {
                        case 1: //printing area of circle; radius known
                            fprintf(file, "The area of your circle with Radius %f is:\n", circle);
                            fprintf(file, "%f\n\n", M_PI * (powf(circle, 2)));
                            break;
                        case 2: //printing area of circle; diameter known
                            fprintf(file, "The area of your circle with Diameter %f is:\n", circle);
                            fprintf(file, "%f\n\n", (M_PI/4) * (powf(circle,2)));
                            break;
                        case 3: //printing area of circle; circumference known
                            fprintf(file, "The area of your circle with Circumference %f is:\n", circle);
                            fprintf(file, "%f\n\n", powf(circle,2)/(4*M_PI));
                        case 4: //printing volume of cube
                            fprintf(file, "The volume of your cube is %llu\n\n", (cube*cube*cube));
                    }   
                }
            fclose(file); //close the file
            } else if(userOpt == '2'){
                return;
            } else {error(); menu();}
        } else {error(); menu();}
    }
}
