#include "socksLib.h"

int SocketDemoUtils_createTcpSocket(){
    int sockFd = 0;

    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    //check for error
    if(sockFd == -1){
        perror("socket");
    }
    
    //TODO: make socket reusable (man setsockopt, man 7 socket)
    
    return sockFd;
}

int SocketDemoUtils_populateAddrInfo(char *port, char *ipAddr, struct sockaddr_in *addr){
    return 0;
}

int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr){
    return 0;
}

int SocketDemoUtils_listen(int sockFd){
    return 0;
}

int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr){
    return 0;
}

int SocketDemoUtils_recv(int sockFd, char **buf){
    return 0;
}

int SocketDemoUtils_send(int sockFd, char *buf, int numBytes){
    return 0;
}
