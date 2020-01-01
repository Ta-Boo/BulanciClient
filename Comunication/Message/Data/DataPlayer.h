//
// Created by tobo on 1/1/20.
//

#ifndef BULANCICLIENT_PLAYER_H
#define BULANCICLIENT_PLAYER_H

enum Facing {top, right, bot, left};


struct DataPlayer {
    int hp;
    int possX;
    int possY;
    Facing facing;

};

#endif //BULANCICLIENT_PLAYER_H
