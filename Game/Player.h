//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_PLAYER_H
#define BULANCICLIENT_PLAYER_H


#include <SDL_surface.h>
#include <SDL_image.h>
#include "../Comunication/Message/Data/PlayerData.h"

//enum Facing {TOP, RIGHT, BOT, LEFT};

class Player {
private:
    int hp;
    SDL_Surface * image;
    double surX = 0;
    double surY = 0;
    int pocetNabojov;
    Facing facing;
    int id;
public:
    void setId(int id);

public:
    int getId() const;

public:
    Player(double surX, double surY);
    ~Player();

    SDL_Surface *getImage() const;
    void setImage(SDL_Surface *image);
    int getSurX() const;
    void setSurX(double surX);
    int getSurY() const;
    void setSurY(double surY);
    void setFacing(Facing facing);
    void zasah();
    int getHp() const;
    void setHp(int hp);
    void update(int x, int y,Facing facing);
    void vystrel();
    void naplnZbran();
    int getPocetNabojov() const;
    Facing getFacing() const;
};


#endif //BULANCICLIENT_PLAYER_H