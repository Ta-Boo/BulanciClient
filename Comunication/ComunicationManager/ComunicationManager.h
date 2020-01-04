//
// Created by Hladek Tobias on 2019-12-27.
//

#ifndef BULANCICLIENT_COMUNICATIONMANAGER_H
#define BULANCICLIENT_COMUNICATIONMANAGER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <thread>
#include "../Message/Message.h"
#include "../../Game/Game.h"

using namespace std;
class ComunicationManager {
private:
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    void listenForMessages(Game* game);
    thread thrd;
    Message* actualMessage;

public:
    ComunicationManager();
    int connectSocket(char* adress, int port);
    void sendMessage(Message* message);
    void activateListening(Game* game);
    void waitForFinish() { thrd.join(); };
    ~ComunicationManager();

};


#endif //BULANCICLIENT_COMUNICATIONMANAGER_H
