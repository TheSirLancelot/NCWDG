#include "socksLib.h"

int main(int argc, char *argv[]){

    int listener = 0, clientFd = 0, check = 0, msgLen = 0, fdmax = 0;
    struct sockaddr_in servAddr, cliAddr;
    char *buf = NULL;
    fd_set master, read_fds;
    struct timeval tv;
    pid_t pid;

    if(argc != 3){
        printf("Usage: ./Server <Server IP> <Server Port>\n");
        exit(EXIT_FAILURE);
    }
    if((isValidIP(argv[1])) <= 0){
        printf("Error: Not a valid IP address\n");
        exit(EXIT_FAILURE);
    }
    if((isValidPort(argv[2])) <= 0){
        exit(EXIT_FAILURE);
    }

    //Create socket
    if((listener = SocketDemoUtils_createTcpSocket()) == -1){
        exit(EXIT_FAILURE);
    }

    //Ensure servAddr memory space is clean
    memset(&servAddr, 0, sizeof(servAddr));

    //Populate address info
    if((SocketDemoUtils_populateAddrInfo(argv[1], argv[2], &servAddr)) == -1){
        exit(EXIT_FAILURE);
    }

    //Bind the socket to the IP/Port
    if((SocketDemoUtils_bind(listener, &servAddr)) == -1){
        exit(EXIT_FAILURE);
    }

    //Set the socket to listen
    if((SocketDemoUtils_listen(listener)) == -1){
         exit(EXIT_FAILURE);
    }

    //Add listener to file descripter set
    FD_SET(listener, &master);

    //Number of file descripters
    fdmax = listener;

    while(1){
        //Copy info from master to a working set
        read_fds = master;

        //set timeout value
        tv.tv_sec = 120;
        tv.tv_usec = 0;

        if((check = select(fdmax+1, &read_fds, NULL, NULL, NULL)) == -1){
            perror("Error with select ");
            exit(EXIT_FAILURE);
        } else if (check == 0){
            printf("Program exiting due to inactivity\n");
            for(int i = 0; i <= fdmax; i++){
                close(i);
            }
            break;
        }

        //TODO: Figure out why clients over 1 sometimes crash

        for(int i = 0; i <= fdmax; i++){ //Looking for data to read
            if(FD_ISSET(i, &read_fds)){ //Data exists
                if(i == listener){ //incoming connection
                    //Accept connection from client
                    if((clientFd = (SocketDemoUtils_accept(listener, &cliAddr))) == -1){
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(clientFd, &master); //add to master set
                    if(clientFd>fdmax){
                        fdmax = clientFd; //keep track of max file descripters
                    }
                    if((pid = fork()) == 0){ //dealing with the child process
                        close(i); //close listener socket on child
                        FD_CLR(i, &master); //remove listener from master list
                    }
                } else {
                    //handle data from client
                    if((msgLen = SocketDemoUtils_recv(clientFd, &buf)) <= 0){
                        //Error or connection closed
                        if(msgLen == 0){
                            //connection closed by client
                        } else {
                            exit(EXIT_FAILURE);
                        }
                        close(i); //close the client socket
                        FD_CLR(i, &master); //remove from the master set
                        break;
                    } else {
                        if((strcmp(buf, "quit\n") == 0) || (strcmp(buf, "Quit\n") == 0)){
                            printf("Goodbye.\n");
                            close(i);
                            FD_CLR(i, &master);
                            if(pid == 0){ //if you were a child,
                                exit(0); //we don't need you. Exit.
                            }
                            break;
                        }
                        //We have data
                        printf("%d bytes received\n", msgLen);
                        if(SocketDemoUtils_send(i, buf, msgLen) == -1){
                            exit(EXIT_FAILURE);
                        }
                    }
                } //end handle data from client
            } //end data exists
        } // end Looking for data to read
    } //end while loop
    free(buf);
    return 0;
} //End main
