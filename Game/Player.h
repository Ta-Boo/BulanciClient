//
// Created by natalia on 30. 12. 2019.
//

#ifndef BULANCICLIENT_PLAYER_H
#define BULANCICLIENT_PLAYER_H

#include <stdlib.h>
#include "SDL_image.h"


class Player {
private:
    SDL_Surface * image;
    double surX = 0;
    double surY = 0;
public:
    Player();
    void pohyb();

    double getSurX() const;

    void setSurX(double surX);

    double getSurY() const;

    void setSurY(double surY);

    SDL_Surface *getImage() const;


};


#endif //BULANCICLIENT_PLAYER_H
