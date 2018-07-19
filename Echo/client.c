#include "socksLib.h"

int main(int argc, char *argv[]){

    int sockFd = 0;
    struct sockaddr_in servAddr = {0};
    char sendLine[BUFF_LEN];

    //Print usage if cmd line error
    if(argc != 3){
        printf("Usage: ./Client <Server IP> <Server port>\n");
        exit(EXIT_FAILURE);
    }

    //TODO: Validate user input

    //Create socket
    if((sockFd = SocketDemoUtils_createTcpSocket()) == -1){
        exit(EXIT_FAILURE);
    }

    //Ensure servAddr memmory space is clean
    memset(&servAddr, 0, sizeof(servAddr));

    //Populate address info
    if((SocketDemoUtils_populateAddrInfo(argv[1], argv[2], &servAddr)) == -1){
        exit(EXIT_FAILURE);
    }

    //Connect to server
    if((connect(sockFd, (struct sockaddr *) &servAddr, sizeof(servAddr))) == -1){
        perror("Error connecting to server\n");
        exit(EXIT_FAILURE);
    }

    //Send message
    memset(&sendLine, 0, sizeof(sendLine));
    while(fgets(sendLine, BUFF_LEN, stdin) != NULL){
        if((SocketDemoUtils_send(sockFd, sendLine, strlen(sendLine))) == -1){
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
