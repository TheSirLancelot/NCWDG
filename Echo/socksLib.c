#include "socksLib.h"

int SocketDemoUtils_createTcpSocket(){
    int sockFd = 0, reuse = 0;

    //Create socket
    if((sockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error creating socket");
        return -1;
    }

    //Set socket to reusable
    if((setsockopt(sockFd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse))) == -1){
        perror("Error setting socket option");
        return -1;
    }
    printf("socket created\n");
    return sockFd;
}

//Populate socket with address info
int SocketDemoUtils_populateAddrInfo(char *ipAddr, char *port, struct sockaddr_in *addr){
    char *endPtr;
    
    addr->sin_family = AF_INET;
    if((inet_pton(AF_INET, ipAddr, &(addr->sin_addr))) ==  -1){
        perror("Error assigning address to socket");
        return -1;
    }
    addr->sin_port = htons(strtol(port, &endPtr, 10));
    printf("address populated\n");
    return 0;
}

//Bind socket to IP/Port
int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr){
    if((bind(sockFd, (struct sockaddr *) addr, sizeof(*addr))) == -1){
        perror("Error binding socket");
        return -1;
    }
    printf("socket binded\n");
    return 0;
}

//Set socket to listen
int SocketDemoUtils_listen(int sockFd){
     if((listen(sockFd, SOMAXCONN)) == -1){
        perror("Error listening on socket");
        return -1;
     }
     printf("Server listening for connections\n");
     return 0;
}

int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr){
    int clientFd = 0;
    int cliLen = sizeof(addr);

    clientFd = accept(sockFd, (struct sockaddr *) addr, &cliLen);
    if(clientFd == -1){
        perror("Error accepting connections");
        return -1;
    }
    printf("Accepted connection.\n");
    return clientFd;
}

int SocketDemoUtils_recv(int sockFd, char **buf){
    int x = 0;
    x = recv(sockFd, buf, BUFF_LEN, 0);
    if(x == -1){
        perror("Error receiving message ");
        return -1;
    }
    return x;
}

int SocketDemoUtils_send(int sockFd, char *buf, int numBytes){
    if((send(sockFd, buf, numBytes, 0)) == -1){
        perror("Error sending message ");
        return -1;
    }
    printf("Message sent\n");
    return 0;
}

