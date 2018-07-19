#include "socksLib.h"

int main(int argc, char *argv[]){

    int sockFd = 0, clientFd = 0, check = 0;
    int totalBuf = BUFF_LEN, remainingBuf = BUFF_LEN;
    struct sockaddr_in servAddr, cliAddr;
    char *buf = NULL;

    if(argc != 3){
        printf("Usage: ./Server <Server IP> <Server Port>\n");
        exit(EXIT_FAILURE);
    }

    //Create socket
    if((sockFd = SocketDemoUtils_createTcpSocket()) == -1){
        exit(EXIT_FAILURE);
    }

    //Ensure servAddr memory space is clean
    memset(&servAddr, 0, sizeof(servAddr));

    //Populate address info
    if((SocketDemoUtils_populateAddrInfo(argv[1], argv[2], &servAddr)) == -1){
        exit(EXIT_FAILURE);
    }

    //Bind the socket to the IP/Port
    if((SocketDemoUtils_bind(sockFd, &servAddr)) == -1){
        exit(EXIT_FAILURE);
    }

    //Set the socket to listen
    if((SocketDemoUtils_listen(sockFd)) == -1){
         exit(EXIT_FAILURE);
    }

    while(1){
        //Accept connection(s) from client
        if((clientFd = (SocketDemoUtils_accept(sockFd, &cliAddr))) == -1){
            exit(EXIT_FAILURE);
        }

        while((check = SocketDemoUtils_recv(clientFd, &buf)) != 0){
            if(check == -1){
                exit(EXIT_FAILURE);
            }
        }
        //TODO: send
        //TODO: use select for looping through connections/sending stuff

        //TODO: shut down connection with client gracefully
        // (e.g. if buf == quit, free, shutdown, etc)
    }

    return 0;
}
