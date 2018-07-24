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
    return sockFd;
}

//Populate socket with address info
int SocketDemoUtils_populateAddrInfo(char *ipAddr, char *port, struct sockaddr_in *addr){
    char *endPtr;
    int convertedPort;

    addr->sin_family = AF_INET;
    if((inet_pton(AF_INET, ipAddr, &(addr->sin_addr))) ==  -1){
        perror("Error assigning address to socket");
        return -1;
    }
    addr->sin_port = htons(strtol(port, &endPtr, 10));
    return 0;
}

//Bind socket to IP/Port
int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr){
    if((bind(sockFd, (struct sockaddr *) addr, sizeof(*addr))) == -1){
        perror("Error binding socket");
        return -1;
    }
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
    int cliLen = sizeof(*addr);

    clientFd = accept(sockFd, (struct sockaddr *) addr, &cliLen);
    if(clientFd == -1){
        perror("Error accepting connections");
        return -1;
    }
    printf("Accepted connection.\n");
    return clientFd;
}

int SocketDemoUtils_recv(int sockFd, char **buf){
    int bytesReceived = 0, totalBuf = 0, status = 0, remainingBuf = 0;

    if(totalBuf == 0){
        //Allocate first bit of memory for buffer
        *buf = (char *)calloc(BUFF_LEN, sizeof(char));
        //Set the sizes to reflect new buffer size
        totalBuf = BUFF_LEN;
        remainingBuf = BUFF_LEN;
    }

    do
    {
        if(remainingBuf < BUFF_LEN){
            if((*buf)[bytesReceived-1] == '\n'){ //EOM reached
                break;
            }

            //reallocate some more memory
            char *tmp;
            totalBuf += BUFF_LEN; //add another BUFF_LEN amount of buffer
            tmp = realloc(*buf, totalBuf); //and reallocate buf to that size
            remainingBuf += BUFF_LEN; //then correct the remaining buffer size

            if(tmp == NULL){ //realloc returns null pointer on failure
                perror("Reallocation error ");
                return -1;
            }
            //Set newly created buf to old buf
            *buf = tmp;
            printf("Total Buffer Size: %d\n", totalBuf);
        } //end rem<BUFF_LEN

        //Receive Message
        if((status = recv(sockFd, *buf+bytesReceived, BUFF_LEN, 0)) == -1){
            perror("Error receiving message ");
            return -1;
        }
        if(status == 0){ //Connection closed by client
            return 0;
        } else if(status > 0){ //We have a message
            bytesReceived += status; //add new bytes to total bytes received
            //adjust the remaining bytes on the buffer
            if((remainingBuf -= status) < 0){
                remainingBuf = 0;
            }
            printf("Status: %d\nBytesReceived: %d\nRemainingBuf: %d\n", status, bytesReceived, remainingBuf);
        } else { //status < 0 = bad
            perror("Error receiving message ");
            return -1;
        }
    } while(status > 0);

    return bytesReceived;
}

int SocketDemoUtils_send(int sockFd, char *buf, int numBytes){
    if((send(sockFd, buf, numBytes, 0)) == -1){
        perror("Error sending message ");
        return -1;
    }
    printf("%d bytes sent\n", numBytes);
    return 0;
}

int isValidIP(char *ipAddress){
    struct sockaddr_in sa;

    if(ipAddress[0] == '.'){
        return -1;
    }

    //will return 0 or -1 if error
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result;
}

int isValidPort(char *port){
    char *endPtr;
        long result;

    if((result = strtol(port, &endPtr, 10)) == 0){
        //There was an error with strtol
        printf("Error: Not a valid port\n");
        return -1;
    }

    if(endPtr == port){
        //no conversion was performed
        printf("Empty port number\n");
        return -1;
    } else if (*endPtr == '\0'){
        //everything was converted
        if(result < 1025 || result > 65535){
            printf("Please enter a port between 1025-65534\n");
            return -1;
        } else {
            return 1;
        }
    } else {
        //there's still string left after the conversion
        printf("Error: Not a valid port\n");
        return -1;
    }

}
