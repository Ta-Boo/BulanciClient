//
// Created by tobo on 1/1/20.
//

#include "PlayerFactory.h"

using namespace boost;

PlayerFactory::PlayerFactory() {}

PlayerFactory::~PlayerFactory() {

}

 PlayerData PlayerFactory::createPlayerData(char *input) {
    //todo Hp:80|posX:600|posY:800|facing:0
     std::vector<string> playerStats;
     boost::split(playerStats, input, boost::is_any_of("|"));
     PlayerData player;
     player.exit = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     player.bulletY = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     player.bulletX = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     Facing facing;
     switch(stoi(playerStats[playerStats.size()-1])) {
         case 0:
             facing = TOP;
             break;
         case 1:
             facing = RIGHT;
             break;
         case 2:
             facing = BOT;
             break;
         case 3:
             facing = LEFT;
             break;
     }
     player.bulletFacing = facing;playerStats.pop_back();
     player.pY = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     player.pX = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     switch(stoi(playerStats[playerStats.size()-1])) {
         case 0:
             facing = TOP;
             break;
         case 1:
             facing = RIGHT;
             break;
         case 2:
             facing = BOT;
             break;
         case 3:
             facing = LEFT;
             break;
     }
     player.facing = facing;playerStats.pop_back();
     player.hp = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();
     player.id = stoi(playerStats[playerStats.size()-1]);playerStats.pop_back();

     return player;
}


