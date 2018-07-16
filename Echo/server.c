#include "socksLib.h"

int main(int argc, char *argv[]){

    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0;
    struct sockaddr_in addr = {0};
    char *buf = NULL;
    
    if(argc != 2){
        //TODO: give a usage message and exit the program
    }

    //create a socket that can connect with TCP/IP
    if((sockFd = SocketDemoUtils_createTcpSocket()) == -1){
        exit(EXIT_FAILURE);
    }

    //TODO: populate the addr variable with the port and ip address
    
    //TODO: bind the socket tot eh ip address and port
    
    //TODO: set up the socket to be listening

    while(1){
        //TODO: accept connection

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
