#include "socksLib.h"

int main(int argc, char *argv[]){

    int listener = 0, clientFd = 0, check = 0, msgLen = 0, fdmax = 0;
    struct sockaddr_in servAddr, cliAddr;
    char *buf = NULL;
    fd_set master, read_fds;

    if(argc != 3){
        printf("Usage: ./Server <Server IP> <Server Port>\n");
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

    //Set the socket to non-blocking
    fcntl(listener, F_SETFL, O_NONBLOCK);

    //Add listener to file descripter set
    FD_SET(listener, &master);

    //Number of file descripters
    fdmax = listener;

    while(1){
        //Copy info from master to a working set
        read_fds = master;
        if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
            perror("Error with select ");
            exit(EXIT_FAILURE);
        }

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
                } else {
                    //handle data from client
                    if((msgLen = SocketDemoUtils_recv(clientFd, &buf)) <= 0){
                        //Error or connection closed
                        if(msgLen == 0){
                            //connection closed by client
                            printf("Goodbye.\n");
                        } else {
                            exit(EXIT_FAILURE);
                        }
                        close(i);
                        FD_CLR(i, &master); //remove from the master set
                    } else {
                        //TODO: WHY ISN'T THIS WORKING?!
                        printf("Message: %s\n", buf);
                        //We have data
                        //if(SocketDemoUtils_send(i, *buf, msgLen) == -1){
                        //    exit(EXIT_FAILURE);
                        //TODO: free?
                        }
                } //end handle data from client
            } //end data exists
        } // end Looking for data to read
    } //end while loop
    return 0;
} //End main
