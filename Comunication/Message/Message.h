//
// Created by tobo on 12/30/19.
//

#ifndef BULANCICLIENT_MESSAGE_H
#define BULANCICLIENT_MESSAGE_H
#define PLAYERS_COUNT 2

#include "Data/DataPlayer.h"
#include <string>
#include <vector>

using namespace std;

class Message
{
public:
    string* actualMessage;
    DataPlayer players[PLAYERS_COUNT]; //todo lepsie  budu  mozno smerniky
    bool exit = false;
public:
    Message();
    ~Message();
    char* toString();


};


#endif //BULANCICLIENT_MESSAGE_H
