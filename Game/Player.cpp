//
// Created by natalia on 1. 1. 2020.
//

#include "Player.h"


Player::Player(double surX, double surY) : surX(surX), surY(surY) {
    this->image = IMG_Load("bulanko.png");
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

}


