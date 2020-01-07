//
// Created by tobo on 1/1/20.
//

#ifndef BULANCICLIENT_PLAYERFACTORY_H
#define BULANCICLIENT_PLAYERFACTORY_H


#include <boost/algorithm/string.hpp>
#include "Data/PlayerData.h"
#include <vector>



class PlayerFactory {
public:
    PlayerFactory();
    ~PlayerFactory();
   static PlayerData createPlayerData(char* input);

};


#endif //BULANCICLIENT_PLAYERFACTORY_H
