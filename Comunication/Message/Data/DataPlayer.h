//
// Created by tobo on 1/1/20.
//

#ifndef BULANCICLIENT_PLAYER_H
#define BULANCICLIENT_PLAYER_H

enum Facing {TOP, RIGHT, BOT, LEFT};

typedef struct DataPlayer {
    int hp;
    int possX;
    int possY;
    Facing facing;

}MyDataPlayer;
#endif //BULANCICLIENT_PLAYER_H
