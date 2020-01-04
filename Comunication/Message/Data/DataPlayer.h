//
// Created by tobo on 1/4/20.
//

#ifndef BULANCICLIENT_DATAPLAYER_H
#define BULANCICLIENT_DATAPLAYER_H
enum Facing {TOP, RIGHT, BOT, LEFT};

class DataPlayer {
public:
    int hp;
    int possX;
    int possY;
    Facing facing;
};


#endif //BULANCICLIENT_DATAPLAYER_H
