#include "myLibrary.h"

void printStr(char *array[], int size){
    printf("Your array of size %d is:\n", size);

    for(int i = 0; i<size; i++){
        printf("Element #%d: %s\n", i, array[i]);
    }
}

long charToLong(char * c){
    char *endptr = NULL;
    long number = 0;
    errno = 0;

    number = strtol(c, &endptr, 10);

    if(c == endptr){
        printf("No digits found, 0 returned\n");
        return 0;
    } else if(errno == ERANGE && number == LONG_MIN){
        printf("Invalid input; Underflow occurred\n");
        return 0;
    } else if(errno == ERANGE && number == LONG_MAX){
        printf("Invalid input; Overflow occurred\n");
        return 0;
    } else if(errno != 0 && number == 0){
        printf("Unspecified error occurred, 0 returned\n");
        return 0;
    } else if(errno == 0 && c && !*endptr){
        return number;
    } else if(errno == 0 && c && *endptr != 0){
        printf("Additional characters remain\n");
        return number;
    }

    return 0;
}
