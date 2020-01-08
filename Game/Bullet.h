//
// Created by natalia on 3. 1. 2020.
//

#ifndef BULANCICLIENT_BULLET_H
#define BULANCICLIENT_BULLET_H


#include <SDL_surface.h>
#include "Player.h"

class Bullet {
private:
    SDL_Surface * image;
    int surX = 0;
    int surY = 0;
    Facing facing;
public:
    void setFacing(Facing facing);

private:
    bool leti = false;
public:
    Bullet();
    ~Bullet();

    int getSurX() const;
    void setSurX(double surX);
    int getSurY() const;
    void setSurY(double surY);
    void update(double x, double y, Facing facing);
    SDL_Surface *getImage() const;
    bool isLeti() const;
    void setLeti(bool leti);
    Facing getFacing() const;
};


#endif //BULANCICLIENT_BULLET_H
