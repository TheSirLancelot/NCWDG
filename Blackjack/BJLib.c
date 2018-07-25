#include "BJLib.h"

//struct definitions
typedef struct card {
    int value; //Ace = 1, 2-10, J = 11, Q = 12, K = 13
    char suit; //H, C, S, D
} Card;

typedef struct player {
    char *name;
    int score; // calculated value of hand
    Card hand[21]; //array of Cards with max amount of 21 cards (21 aces)
} Player;

//symbols for suits
const wchar_t SPADE = 0X2664;
const wchar_t HEART = 0x2661;
const wchar_t DIAMOND = 0x2662;
const wchar_t CLUB = 0x2667;

//function to display the menu
void menu(){
    char *userInput = NULL; //buffer for user input
    size_t bufLen = 2; //should only be getting 2 characters (num + \n)

    //make the screen pretty
    if((system("clear")) < 0){
        perror("couldn't clear screen ");
    }

    if(1==1){ //ASCII art in a loop so I can hide it in the editor; Ignore this
        printf("\n\n\nWELCOME TO CTN1 WEIR'S AMAZING GAME OF...\n\n");
        printf("B)bbbb    L)          A)aa      C)ccc   K)   kk   J)jjjjjj    A)aa      C)ccc   K)   kk \n");
        printf("B)   bb   L)         A)  aa    C)   cc  K)  kk        J)     A)  aa    C)   cc  K)  kk  \n");
        printf("B)bbbb    L)        A)    aa  C)        K)kkk         J)    A)    aa  C)        K)kkk   \n");
        printf("B)   bb   L)        A)aaaaaa  C)        K)  kk    J)  jj    A)aaaaaa  C)        K)  kk  \n");
        printf("B)    bb  L)        A)    aa   C)   cc  K)   kk   J)  jj    A)    aa   C)   cc  K)   kk \n");
        printf("B)bbbbb   L)llllll  A)    aa    C)ccc   K)    kk   J)jj     A)    aa    C)ccc   K)    kk\n");
        printf("\n\n");
    }

    do
    {
        printf("What would you like to do?\n");
        printf("(1) Play the Game!\n(2) See the Rules!\n(3) Get the Eff Out of Here!\n");
        if((getline(&userInput, &bufLen, stdin)) < 0){
            perror("getline error ");
            exit(EXIT_FAILURE);
        }
        switch(*userInput){
            case '1':
                game();
                break;
            case '2':
                rules();
                break;
            case '3':
                cleanup();
                break;
            default:
                printf("Please choose an appropriate option:\n\n");
        }
    } while((strcmp(userInput, "1\n") != 0) && (strcmp(userInput, "2\n") != 0) && (strcmp(userInput, "3\n") != 0));
} // end menu()

//function to play the game
void game(){
    int gameNum = 0;
    char *name = NULL;
    size_t bufLen = 21;

    //make the screen pretty
    if((system("clear")) < 0){
        perror("couldn't clear screen ");
    }

    //Get the user's name
    if(gameNum == 0){
        int strLen;

        printf("What is your name? [20 chars max]\n");
        if((getline(&name, &bufLen, stdin)) < 0){
            perror("getline error ");
            exit(EXIT_FAILURE);
        }
        strLen = (strlen(name));
        //get rid of newline
        if(name[strLen-1] == '\n'){
            name[strLen-1] = '\0';
        }
    }

    printf("\n\nGame Number %d:\n", gameNum);

    //create two players
    Player *player = newPlayer(name);
    Player *dealer = newPlayer("Dealer");

    printf("Your name is %s\n", player->name);
    printf("The dealer's name is: %s\n", dealer->name);

    cleanup();
} //end game()

//function to display rules
void rules(){
    char *userInput = NULL; //buffer for user input
    size_t bufLen = 2; //should only be getting 2 characters (num + \n)

    //make the screen pretty
    if((system("clear")) < 0){
        perror("couldn't clear screen ");
    }
    printf("\n\nThe object of BlackJack is simple: BEAT THE DEALER! Here's how to go about that:\n\n");
    printf("\t- Aces are 1 or 11 points, 2 to 9 according to pip value, and tens/face cards equal ten.\n\n");
    printf("\t- The value of a hand is the sum of the point values of the individual cards.\n\tA \"blackjack\" is the highest hand (an ace and any 10-point card).\n\n");
    printf("\t- The dealer will give two cards to the player and two cards to himself. \n\tOne of the dealer cards is dealt face up.\n\n");
    printf("\t- If the dealer has a ten or an ace showing, he will look to see if he has a blackjack. \n\tIf he does, then he will turn it over immediately.\n\n");
    printf("\t- If the dealer has blackjack, the player loses unless he/she also has blakjack (push).\n\n");
    printf("\t- Play begins with the player. The following are the choices available to the player:\n");
    printf("\t\t- Stand: Player stands pat with his cards.\n");
    printf("\t\t- Hit: Player draws another card (and more if he/she wishes). \n\t\tIf this card causes the total points to exceed 21 (\"busting\") then he/she loses.\n\n");
    printf("\t- After the player has had his/her turn, the dealer will turn over his/her hole card. \n\tThe dealer will always hit 16 or less.\n\n");
    printf("\t- If the dealer goes over 21 points, then the player (if they didn't bust) will win.\n\n");
    printf("\t- If the dealer doesn't bust, then the higher point total (player vs dealer) will win.\n\n");
    printf("\t- If the dealer and player have the same total (21 and under), everyone wins!\n");

    printf("\n\nClear as mud?? [y/n]\n");
    while(1){
        if((getline(&userInput, &bufLen, stdin)) < 0){
            perror("getline error ");
            exit(EXIT_FAILURE);
        }
        switch(*userInput){
            case 'y':
            case 'Y':
                printf("Ok! Good! Here we go...\n");
                printf("In 3..\n");
                sleep(1);
                printf("2..\n");
                sleep(1);
                printf("1..\n");
                sleep(1);
                game();
                break;
            case 'n':
            case 'N':
                printf("Too bad, you're going anyway...\n");
                printf("In 3..\n");
                sleep(1);
                printf("2..\n");
                sleep(1);
                printf("1..\n");
                sleep(1);
                game();
                break;
            default:
                printf("C'mon... yes or no.. Not that difficult..\n");
        }
    }
} //end rules()

//function to cleanup and exit
void cleanup(){
    exit(EXIT_SUCCESS);
} //end cleanup()

Player *newPlayer(char *name){
    Player *returnVal;
    //Attempt to allocate space for a new player
    returnVal = (Player *)calloc(1, sizeof(Player));
    if (returnVal == NULL){
        perror("calloc error ");
        exit(EXIT_FAILURE);
    }

    //Set player name
    returnVal->name = name;

    return returnVal;
}
