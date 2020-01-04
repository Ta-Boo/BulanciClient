//
// Created by Hladek Tobias on 2019-12-27.
//
#include "ComunicationManager.h"
ComunicationManager::ComunicationManager(){
    actualMessage = new Message();

};


ComunicationManager::~ComunicationManager() {
    close(sockfd);
    delete actualMessage;
}

int ComunicationManager::connectSocket(char *adress, int port) {

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
    printf("Conected to server\n");
    return 0;
}

void ComunicationManager::sendMessage(Message* message) {
        printf("sending... \n");
//        bzero(buffer,256);
//        fgets(buffer, 255, stdin);
//        char* sending = "prva";//message->toString();
        write(sockfd, message->toString() , strlen(message->toString())+1);
    printf("sent! \n");


}

void ComunicationManager::activateListening() {
    thrd = thread(&ComunicationManager::listenForMessages,this);
}



//MARK: private
void ComunicationManager::listenForMessages() {
    char buffer[256];
    while(true) {
        bzero(buffer,256);
        read(sockfd, buffer, 255);

        if (strcmp(buffer, "FINISH") == 0 ) {
            Message message;
            message.exit = true;
            sendMessage(&message);
            break;
        }
        printf("%s\n",buffer);
    }
}






