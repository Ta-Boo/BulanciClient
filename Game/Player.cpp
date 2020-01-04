//
// Created by natalia on 1. 1. 2020.
//

#include "Player.h"


Player::Player(double surX, double surY) : surX(surX), surY(surY) {
//Player::Player() {
    this->hp = 0;
    this->facing = RIGHT;
    this->image = IMG_Load("/home/natalia/CLionProjects/BulanciClient/hrac.png");
}

SDL_Surface *Player::getImage() const {
    return image;
}

void Player::setImage(SDL_Surface *image) {
    Player::image = image;
}

double Player::getSurX() const {
    return surX;
}

void Player::setSurX(double surX) {
    Player::surX = surX;
}

double Player::getSurY() const {
    return surY;
}

void Player::setSurY(double surY) {
    Player::surY = surY;
}

Player::~Player() {
    delete image;
}

void Player::update(int x, int y,Facing facing) {
    this->surX += x;
    this->surY += y;
    this->facing = facing;
    /*switch(facing) {
        case TOP:
            this->image = IMG_Load("/home/natalia/CLionProjects/BulanciClient/hracUP.png");
            break;
        case RIGHT:
            this->image = IMG_Load("/home/natalia/CLionProjects/BulanciClient/hrac.png");
            break;
        case LEFT:
            this->image = IMG_Load("/home/natalia/CLionProjects/BulanciClient/hracLEFT.png");
            break;
        case BOT:
            this->image = IMG_Load("/home/natalia/CLionProjects/BulanciClient/hracDOWN.png");
            break;
    }*/
}

Facing Player::getFacing() const {
    return facing;
}


