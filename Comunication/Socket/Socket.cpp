//
// Created by Hladek Tobias on 2019-12-27.
//
#include "Socket.h"
Socket::Socket(){};

int Socket::connectSocket(char *adress, int port) {

    server = gethostbyname(adress);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 3;
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }

    return 0;
}

char* Socket::sendMessage() {
        printf("Please enter a message: ");
        bzero(buffer,256);
        fgets(buffer, 255, stdin);
        write(sockfd, buffer, strlen(buffer));
    return "";
}

char *Socket::listenForMessages() {
    while(true) {
//        this->sendMessage();
        bzero(buffer,256);
        read(sockfd, buffer, 255);
        if (strcmp(buffer, "EXITS\n") == 0 ) {
            break;
        }
        printf("%s\n",buffer);
    }
    return nullptr;
}

Socket::~Socket() {
    close(sockfd);
}





