#include "socksLib.h"

int main(int argc, char *argv[]){

    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
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
        //TODO: accept connection
        if((clientFd = (SocketDemoUtils_accept(sockFd, &cliAddr))) == -1){
            exit(EXIT_FAILURE);
        }

        //TODO: once connection is accepted, receive entire message
        //      from the client and then send it back.

        while(1){
            //TODO: allocate memory for receiving

            //TODO: receive the message until it has been completely received

            //TODO: send the message to the client

            //TODO: clean up the buffer memory to avoid memory leak
        }
        //TODO: shut down connection with client gracefully
    }

    return 0;
}
