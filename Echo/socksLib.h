#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int SocketDemoUtils_createTcpSocket();
int SocketDemoUtils_populateAddrInfo(char *ipAddr, char *port, struct sockaddr_in *addr);
int SocketDemoUtils_bind(int sockFd, struct sockaddr_in *addr);
int SocketDemoUtils_listen(int sockFd);
int SocketDemoUtils_accept(int sockFd, struct sockaddr_in *addr);
int SocketDemoUtils_recv(int sockFd, char **buf);
int SocketDemoUtils_send(int sockFd, char *buf, int numBytes);
