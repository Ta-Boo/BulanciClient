//
// Created by Hladek Tobias on 2019-12-27.
//
#include "ComunicationManager.h"
#include "../../Game/Game.h"



ComunicationManager::ComunicationManager(){

};


ComunicationManager::~ComunicationManager() {
    close(sockfd);
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

void ComunicationManager::sendMessage(PlayerData message) {
    cout << "sending = " << message.toString() << endl;
    char mess[256] = "";
    bzero(mess,256);
    strcpy(mess, message.toString().c_str());
    write(sockfd, mess , strlen(mess)+1);
}

void ComunicationManager::activateListening(Game* game) {
    thrd = thread(&ComunicationManager::listenForMessages,this, game);
}

//MARK: private
void ComunicationManager::listenForMessages(Game* game) {
    char buffer[256];
    while(true) {
        bzero(buffer,256);
        read(sockfd, buffer, 255);
        cout << "i received : " << buffer << endl;
        PlayerData data = PlayerFactory::createPlayerData(buffer);
        if(data.exit) {
            game->updateFromMessage(data);
            break;
        }
        game->updateFromMessage(data);
    }
    cout << "KONCIM" << endl;
}






