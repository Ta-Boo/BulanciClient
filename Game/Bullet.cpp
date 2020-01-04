//
// Created by natalia on 3. 1. 2020.
//

#include "Bullet.h"

Bullet::Bullet() {
    this->image = IMG_Load("bullet.png");
    this->facing = RIGHT;
}

double Bullet::getSurX() const {
    return surX;
}

void Bullet::setSurX(double surX) {
    Bullet::surX = surX;
}

double Bullet::getSurY() const {
    return surY;
}

void Bullet::setSurY(double surY) {
    Bullet::surY = surY;
}

SDL_Surface *Bullet::getImage() const {
    return image;
}

Facing Bullet::getFacing() const {
    return facing;
}

void Bullet::update(double x, double y, Facing facing) {
    this->surX += x;
    this->surY += y;
    this->facing = facing;
}

Bullet::~Bullet() {
//    delete image;
SDL_FreeSurface(image);
}

bool Bullet::isLeti() const {
    return leti;
}

void Bullet::setLeti(bool leti) {
    Bullet::leti = leti;
}
