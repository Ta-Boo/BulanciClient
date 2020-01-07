//
// Created by tobo on 1/4/20.
//

#ifndef BULANCICLIENT_DATAPLAYER_H
#define BULANCICLIENT_DATAPLAYER_H
enum Facing {TOP, RIGHT, BOT, LEFT};

class DataPlayer {
public:
    int id;
    int hp;
    int pX;
    int pY;
    Facing facing;

    int bulletFacing;
    int bulletX;
    int bulletY;

    bool exit = false;
};


#endif //BULANCICLIENT_DATAPLAYER_H
