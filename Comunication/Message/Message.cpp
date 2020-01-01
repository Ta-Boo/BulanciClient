//
// Created by tobo on 12/30/19.
//

#include <iostream>
#include "Message.h"
#include "Data/DataPlayer.h"

Message::Message() {
    actualMessage = new string();
}

Message::~Message() {
    std::cout << *actualMessage <<endl;
    delete actualMessage;
    std::cout << *actualMessage <<endl;
}

char* Message::toString() {
//    actualMessage = new string();
    for (DataPlayer player : players) {
        string playerString = "Hp:" + to_string(player.hp) + "|" + "posX:" + to_string(player.possX) + "|" +
                "posY" + to_string(player.possY) + "|" + "facing:" + to_string(player.facing) + "||";
        *actualMessage += playerString;
    }
    *actualMessage += "}";

    char* returningString  = &(*actualMessage)[0];
    return returningString;
}
