#include "BJLib.h"

//struct definitions
typedef struct card {
    char value; //Ace = 1, 2-10, J = 11, Q = 12, K = 13
    wchar_t suit; //H, C, S, D
} Card;

typedef struct player {
    char *name;
    int score; // calculated value of hand
    Card hand[21]; //array of Cards with max amount of 21 cards (21 aces)
} Player;

//function to display the menu
void menu(){
    char *userInput = NULL; //buffer for user input
    size_t bufLen = 2; //should only be getting 2 characters (num + \n)

    if((system("clear")) < 0){
        perror("system error");
        exit(EXIT_FAILURE);
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
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Please choose an appropriate option:\n\n");
        }
    } while((strcmp(userInput, "1\n") != 0) && (strcmp(userInput, "2\n") != 0) && (strcmp(userInput, "3\n") != 0));
} // end menu()

//function to play the game
void game(){
    char *choice = NULL; //hits or stands
    size_t bufLen = 21; //for getline
    int value; //for Card
    int index; //index for picking suits/values
    int stay = 0; //for checking if player wants to stay
    int playerBust = 0; //whether player busted
    int dealerBust = 0; //whether dealer busted
    wchar_t suits[] = {SPADE, HEART, DIAMOND, CLUB};
    char cards[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};

    //Get the user's name
    if(gameNum == 0){
        int strLen;

        printf("\n\n\nWhat is your name? [20 chars max]:\n");
        if((getline(&name, &bufLen, stdin)) < 0){
            perror("getline error ");
            exit(EXIT_FAILURE);
        }
        strLen = (strlen(name));
        //get rid of newline
        if(name[strLen-1] == '\n'){ //Helps with printing
            name[strLen-1] = '\0';
        }
    } //end get user's name

    printf("\n\nGame Number %d:\n\n\n", ++gameNum);

    //create two players
    Player *player = newPlayer(name);
    Player *dealer = newPlayer("Dealer");

    //Deal the first cards
    for(int i = 0; i < 2; i++){
        index = (rand() % 13); //rand # 0-12
        player->hand[i].value = cards[index];
        index = (rand() % 4); //rand # 0-3
        player->hand[i].suit = suits[index]; //assign suit to card
        //repeat for dealer
        index = (rand() % 13);
        dealer->hand[i].value = cards[index];
        index = (rand() % 4);
        dealer->hand[i].suit = suits[index];
    } //end deal first cards

    //Calculate the first totals:
    if(dealer->hand[1].value == 'A' || dealer->hand[1].value == 'K' || dealer->hand[1].value == 'Q' || dealer->hand[1].value == 'J' || dealer->hand[1].value == 'T'){
        //check for blackjack
        score(dealer, 0);
        if(dealer->score == 21){
            score(player, 0);
            show(dealer, 2, 0);
            show(player, 2, 0);
            printf("Dealer has BlackJack!\n");
            //Check to see if player has blackjack for the push
            if(player->score == 21){
                printf("%s ALSO has BlackJack!\n", player->name);
            }
            playAgain(player, dealer);
        }
    } //end calculate first totals
    //If dealer doesn't have blackjack
    score(dealer, 1);
    score(player, 0);

    //Show the first 2 cards
    show(dealer, 2, 1);
    show(player, 2, 0);

    if(player->score == 21){
        printf("%s WINS WITH A BLACKJACK!\n", player->name);
        playAgain(player, dealer);
    }

    int playerCards = 2; //where the next card will go in the hand array
    int dealerCards = 2;

    while(player->score <= 21 && stay == 0){
        printf("[H]it or [S]tand?\n");
        if((getline(&choice, &bufLen, stdin)) < 0){
            perror("getline error ");
            exit(EXIT_FAILURE);
        }
        switch(*choice){
            case 'H':
            case 'h':
                index = (rand() % 13); //rand # 0-12
                player->hand[playerCards].value = cards[index];
                index = (rand() % 4); //rand # 0-3
                player->hand[playerCards].suit = suits[index]; //assign suit to card
                playerCards++;
                //rescore hand
                score(player,0);
                //show new hands
                printf("\n\n");
                show(dealer,2,1);
                show(player,playerCards,0);
                break;
            case 'S':
            case 's':
                printf("%s stays with %d\n", player->name, player->score);
                stay = 1;
                break;
            default:
                printf("H to hit, S to stay\n");
        } //end switch
    } //end while

    if(player->score > 21){
        playerBust = 1;
        printf("YOU BUSTED!\n");
    }

    sleep(1);
    printf("Dealer's turn:\n");
    sleep(2);
    //rescore with dealer's facedown card
    score(dealer, 0);
    //show hands again
    show(dealer,dealerCards,0);
    show(player, playerCards, 0);
    while(dealer->score <= 21){
        if(dealer->score < 17){
            sleep(2);
            printf("\nDealer Hits!\n\n");
            index = (rand() % 13); //rand # 0-12
            dealer->hand[dealerCards].value = cards[index];
            index = (rand() % 4); //rand # 0-3
            dealer->hand[dealerCards].suit = suits[index]; //assign suit to card
            dealerCards++;
            //rescore hand
            score(dealer,0);
            //show new hands
            printf("\n\n");
            show(dealer,dealerCards,0);
            show(player,playerCards,0);
        } else { //card is between 17-21
            printf("%s stays with %d\n\n", dealer->name, dealer->score);
            break;
        }
    } //end while
    sleep(1);

    if(dealer->score > 21){
        dealerBust = 1;
        printf("THE DEALER BUSTED!\n");
    }

    if(playerBust == 0 && dealerBust == 1){
        printf("%s WINS!!\n\n", player->name);
    } else if(dealerBust == 0 && playerBust ==1){
        printf("THE DEALER WON!\n\n");
    } else if(playerBust == 0 && (player->score > dealer->score)){
        printf("%s WINS!!\n\n", player->name);
    } else if(dealerBust == 0 && (dealer->score > player->score)){
        printf("THE DEALER WON!\n\n");
    } else if(dealerBust == 1 && playerBust == 1){
        printf("The dealer busted, but you still lost..\n\n");
    } else if(player->score == dealer->score){
        printf("YOU PUSHED!\n\n");
    }

    playAgain(player, dealer);
} //end game()

//function to display rules
void rules(){
    char *userInput = NULL; //buffer for user input
    size_t bufLen = 2; //should only be getting 2 characters (num + \n)

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

void show(Player *p, int numCards, int hasHole){
    int spaces = (numCards * 2) + (numCards - 1);

    printf(" %s:\n", p->name);
    printf(" ");
    for(int i = 0; i<spaces; i++){
        printf("-");
    }
    printf("\n|");
    for(int i = 0; i<spaces; i++){
        printf(" ");
    }
    printf("|\n|");
    for(int i = 0; i<numCards; i++){
        if(hasHole == 1 && i == 0){ //first card needs to be "face down"
            printf("??");
        } else {
            printf("%c%lc", p->hand[i].value, p->hand[i].suit);
        }
        //put a comma in between them (except for the last one)
        if(i < (numCards -1)){
            printf(",");
        }
    }
    printf("| = %d\n|", p->score);
    for(int i = 0; i<spaces; i++){
        printf(" ");
    }
    printf("|\n");
    printf(" ");
    for(int i = 0; i<spaces; i++){
        printf("-");
    }
    printf("\n\n");
}

void score(Player *p, int hasHole){
    int tmpScore = 0, aceCounter = 0;

    for(int i = 0; i < 22; i++){ //22 is the max number of cards we could have
        if(hasHole == 1){
            i++; //skips the first card if dealer's card is face down
        }
        switch(p->hand[i].value){ //get value, add to total value
            case 'A':
                aceCounter++; //keep track of the number of aces
                tmpScore += 11;
                break;
            case '2':
                tmpScore += 2;
                break;
            case '3':
                tmpScore += 3;
                break;
            case '4':
                tmpScore += 4;
                break;
            case '5':
                tmpScore += 5;
                break;
            case '6':
                tmpScore += 6;
                break;
            case '7':
                tmpScore += 7;
                break;
            case '8':
                tmpScore += 8;
                break;
            case '9':
                tmpScore += 9;
                break;
            case 'T':
            case 'J':
            case 'Q':
            case 'K':
                tmpScore += 10;
                break;
        }
    }

    while(aceCounter > 0 && tmpScore > 21){
        aceCounter--;
        tmpScore -= 10;
    }

    p->score = tmpScore;
}

void playAgain(Player *p, Player *d){
    char *choice = NULL; //hits or stands
    size_t bufLen = 21; //for getline

    printf("\nWould you like to play again [Y/N]?\n");
    if((getline(&choice, &bufLen, stdin)) < 0){
        perror("getline error ");
        exit(EXIT_FAILURE);
    }
    while(1){
    switch(*choice){
        case 'Y':
        case 'y':
            memset(&p->hand, 0, sizeof(p->hand)); //clear out hands
            memset(&d->hand, 0, sizeof(d->hand));
            game();
            break;
        case 'N':
        case 'n':
            free(p); //free player
            free(d); //free dealer
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Please enter Y or N\n");
        }
    }
}
