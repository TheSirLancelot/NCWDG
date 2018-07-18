#include "socksLib.h"

int main(int argc, char *argv[]){

    int sockFd = 0, clientFd = 0, bytesReceived = 0, bytesSent = 0, status = 0; 
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

        buf = (char *)malloc(sizeof(char)*BUFF_LEN); //Allocate first bit of memory for buffer
                
        do {
            if(remainingBuf == 0){ //if remaining buffer is 0, we may need more
                if(buf[totalBuf-1] == '\n' || buf[totalBuf-1] == '\0'){ //unless the last char was on of these
                    break;
                }
                char *tmp;
                
                totalBuf += BUFF_LEN; //add another BUFF_LEN amount of buffer
                tmp = realloc(buf, totalBuf); //and reallocate buf to that size
                remainingBuf += BUFF_LEN; //then correct the remaining buffer size

                if(tmp == NULL){ //realloc returns null pointer on failure
                    perror("Reallocation error ");
                    exit(EXIT_FAILURE);
                }

                buf = tmp;
            }

        status = SocketDemoUtils_recv(clientFd, &buf);
        if(status == 0){
            printf("Msg received\n");
        } else if (status > 0){
            bytesReceived += status;
            remainingBuf -= status;
            printf("status: %d\n", status);
        } else { //status < 0 = bad
            exit(EXIT_FAILURE);
        }
        } while(status > 0);

        //TODO: shut down connection with client gracefully
        // (e.g. if buf == quit, free, shutdown, etc)
    }

    return 0;
}
