#include "socksLib.h"

int SocketDemoUtils_createTcpSocket(){
    int sockFd = 0, reuse = 0;

    //Create socket
    if((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error creating socket\n");
        return -1
    } 
    
    //Set socket to reusable
    if((setsockopt(sockFd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse))) == -1){
        perror("Error setting socket option\n");
        return -1;
    }

    return sockFd;
}

int SocketDemoUtils_populateAddrInfo(char *ipAddr, char *port, struct sockaddr_in *addr){
    addr->sin_family = AF_INET;
    if((inet_pton(AF_INET, *ipAddr, &(addr->sin_addr))) ==  -1){
        perror("Error assigning address to socket\n");
        return -1;
    }
    addr->sin_port = htons(*port);
    return 0;
}

//TODO: Below functionality
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
