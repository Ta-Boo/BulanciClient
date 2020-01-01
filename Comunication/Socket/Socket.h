//
// Created by Hladek Tobias on 2019-12-27.
//

#ifndef BULANCICLIENT_SOCKET_H
#define BULANCICLIENT_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


class Socket {
private:
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];


public:
    Socket();
    int connectSocket(char* adress, int port);
    char* sendMessage();
    char* listenForMessages();
    ~Socket();

};


#endif //BULANCICLIENT_SOCKET_H
