#include "myLibrary.h"

int main(int argc, char* argv[]){
    //printStr(argv, argc);
    
    /*char *strings[] = {
        "dice roller",
        "area of a circle",
        "volume of a cube",
        "hi/low game",
        "quit"
    };

    printStr(strings, (sizeof(strings)/sizeof(char*)));
    return 0;*/

    char *test[] = {
        "356",
        "asdfa",
        "9223372036854775807",
        "9223372036854775808",
        "-9223372036854775808",
        "-9223372036854775809"
    };

    for(int i=0;i<6;i++){
        printf("Testing %s (string length: %d):\n", test[i], strlen(test[i]));
        printf("%ld\n\n", charToLong(test[i]));
    }

}
