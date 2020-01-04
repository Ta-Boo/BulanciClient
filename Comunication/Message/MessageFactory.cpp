//
// Created by tobo on 1/1/20.
//

#include "MessageFactory.h"

using namespace boost;

MessageFactory::MessageFactory() {}

MessageFactory::~MessageFactory() {

}

 Message MessageFactory::createMessage(char *input) {
    //todo Hp:80|posX:600|posY:800|facing:0
    std::vector<string> players;
    std::vector<string> parts;
    boost::split(players, input, boost::is_any_of("*"));
    Message message;
    for(int i = 0;  i < PLAYERS_COUNT; i++ ) {
        boost::split(parts, players[i], boost::is_any_of("|"));

        Facing facing;
        switch(stoi(parts[parts.size()-1])) {
            case 1:
                facing = TOP;
                break;
            case 2:
                facing = RIGHT;
                break;
            case 3:
                facing = BOT;
                break;
            case 4:
                facing = LEFT;
                break;

            default:
                facing = TOP;
                break;
        }
        message.players[i].facing = facing;
        parts.pop_back();
        message.players[i].possY = stoi(parts[parts.size()-1]); parts.pop_back();
        message.players[i].possX = stoi(parts[parts.size()-1]); parts.pop_back();
        message.players[i].hp = stoi(parts[parts.size()-1]); parts.pop_back();


    }
    return message;
}


