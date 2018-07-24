#include "socksLib.h"

int main(int argc, char *argv[]){

    //file descripters, etc.
    int listener = 0, clientFd = 0, check = 0, msgLen = 0, fdmax = 0;
    struct sockaddr_in servAddr, cliAddr; //IP address structs
    char *buf = NULL; //receving buffer
    char *sendLine = NULL; //sendline for server stdin
    fd_set master, read_fds; //filesets for select
    struct timeval tv; //for a timeout if being used
    pid_t pid = getpid(); //pid for fork
    size_t bufLen = BUFF_LEN; //buffer length for getline

    if(argc != 3){
        printf("Usage: ./Server <Server IP> <Server Port>\n");
        exit(EXIT_FAILURE);
    }
    //checking IP
    if((isValidIP(argv[1])) <= 0){
        printf("Error: Not a valid IP address\n");
        exit(EXIT_FAILURE);
    }
    //checking port
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

    //Add stdin to be able to quit
    FD_SET(0, &master);

    //Number of file descripters
    fdmax = listener;
    printf("Listener: %d\n", listener);

    while(1){
        //Copy info from master to a working set
        read_fds = master;

        //set timeout value (uncomment and change select param)
        //tv.tv_sec = 120;
        //tv.tv_usec = 0;

        //Look at all the file descripters and continue on an event
        if((check = select(fdmax+1, &read_fds, NULL, NULL, NULL)) == -1){
            perror("Error with select ");
            exit(EXIT_FAILURE);
        } else if (check == 0){ //only true if using a timeout
            printf("Program exiting due to inactivity\n");
            for(int i = 0; i <= fdmax; i++){
                close(i);
            }
            break;
        }

        for(int i = 0; i <= fdmax; i++){ //Looking for data to read
            if(FD_ISSET(i, &read_fds)){ //Data exists
                if(i == listener){ //incoming connection
                    printf("\nPid %d is Selecting: %d \n", pid, i);
                    //Accept connection from client
                    if((clientFd = (SocketDemoUtils_accept(listener, &cliAddr))) == -1){
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(clientFd, &master); //add to master set
                    if(clientFd>fdmax){
                        fdmax = clientFd; //keep track of max file descripters
                    }
                    if((pid = fork()) == 0){ //dealing with the child process
                        printf("My pid is: %d\n", pid);
                        printf("Closing: %d\n", i);
                        close(i); //close listener socket on child
                        FD_CLR(i, &master); //remove listener from master list
                    }
                } else if(i == 0){ //something is on the server's STDIN
                    printf("\nPid %d is Selecting: %d \n", pid, i);
                    if((getline(&sendLine, &bufLen, stdin)) == -1){
                        perror("input error on stdin ");
                    }
                    if((strcmp(sendLine, "quit\n") == 0) || (strcmp(sendLine, "Quit\n") == 0)){
                        printf("Exiting server..\n");
                        for(int i = 0; i <= fdmax; i++){ //close all sockets
                            close(i);
                        }
                        break; //break out of while loop
                    } else {
                        printf("Type 'quit' to quit\n");
                    }
                } else {
                    if(pid == 0){
                        printf("\nPid %d is Selecting: %d \n", pid, i);
                        //handle data from client
                        if((msgLen = SocketDemoUtils_recv(i, &buf)) <= 0){
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
                                printf("Goodbye from pid: %d.\n", pid);
                                close(i);
                                FD_CLR(i, &master);
                                if(pid == 0){ //if you were a child,
                                    printf("closing pid: %d\n", pid);
                                    exit(0); //we don't need you. Exit.
                                }
                                break;
                            }
                            //We have data
                            printf("%d bytes received\n", msgLen);
                            //send it back
                            if(SocketDemoUtils_send(i, buf, msgLen) == -1){
                                exit(EXIT_FAILURE);
                            }
                            free(buf);
                        }
                    }
                } //end handle data from client
            } //end data exists
        } // end Looking for data to read
    } //end while loop
    //free the buffers
    free(sendLine);
    free(buf);
    return 0; //exit cleanly
} //End main
