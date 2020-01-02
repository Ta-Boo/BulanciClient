//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_PLAYER_H
#define BULANCICLIENT_PLAYER_H


#include <SDL_surface.h>
#include <SDL_image.h>

class Player {
private:
    SDL_Surface * image;
    double surX;
    double surY;
public:
    Player(double surX, double surY);

    virtual ~Player();

    SDL_Surface *getImage() const;

    void setImage(SDL_Surface *image);

    double getSurX() const;

    void setSurX(double surX);

    double getSurY() const;

    void setSurY(double surY);
};


#endif //BULANCICLIENT_PLAYER_H
