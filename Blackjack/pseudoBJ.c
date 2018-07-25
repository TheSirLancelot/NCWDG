//explain the rules to the user, ask if they're ready to play

//calloc two memory locations for a player and a dealer
    typedef struct card {
        int value; //Ace = 1, 2-10, J = 11, Q = 12, K = 13
        char suit; //H, C, S, D
    } Card;

    typedef struct player {
        int score; // calculated value of hand
        Card hand[21]; array of Cards with max amount of 21 cards (21 aces)
    } Player;

//deal out two cards to the player, held in the above data structures

//user hits (randomly add a new card into his hand[]) until he busts or stays

//Dealer automatically hits until he hits 17 or busts

//Whoever hand is higher without going over 21 wins. Tie == push

//pseudo alorithm for determining int score:

foreach card in (hand){
    if(score > 21 || card == ACE){
        player.hand[card].value == 1;
    }
    score += player.hand[card].value;
    }
}
