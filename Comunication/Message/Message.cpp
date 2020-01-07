//
// Created by tobo on 12/30/19.
//

#include <iostream>
#include "Message.h"
#include "Data/DataPlayer.h"

Message::Message() {
//    actualMessage = new  string();
//    players[0].facing = TOP;
//    players[0].hp = 80;
//    players[0].pX = 400;
//    players[0].pY = 600;
//
//    players[1].facing = BOT;
//    players[1].hp = 30;
//    players[1].pX = 200;
//    players[1].pY = 900;
}

Message::~Message() {
    delete actualMessage;
}

char* Message::toString() {
    if(exit){
        return "EXIT";
    }
    int counter =1;
    for (DataPlayer player : players) {
        string playerString = to_string(player.hp) + "|" + to_string(player.pX) +
                              "|" + to_string(player.pY) + "|" + to_string(player.facing) ;
        if (counter < PLAYERS_COUNT) {
            playerString+="*";
        }
        counter++;
        *actualMessage += playerString;
    }

    return &(*actualMessage)[0];
}
