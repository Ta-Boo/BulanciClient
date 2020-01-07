//
// Created by natalia on 1. 1. 2020.
//

#include "Player.h"


Player::Player(double surX, double surY) : surX(surX), surY(surY) {
//Player::Player() {
    this->hp = 100;
    this->facing = RIGHT;
    this->image = IMG_Load("hrac.png");
    this->pocetNabojov = 5;
}

SDL_Surface *Player::getImage() const {
    return image;
}

void Player::setImage(SDL_Surface *image) {
    Player::image = image;
}

int Player::getSurX() const {
    return surX;
}

void Player::setSurX(double surX) {
    Player::surX = surX;
}

int Player::getSurY() const {
    return surY;
}

void Player::setSurY(double surY) {
    Player::surY = surY;
}

Player::~Player() {
}

void Player::update(int x, int y,Facing facing) {
    this->surX += x;
    this->surY += y;
    this->facing = facing;
}

Facing Player::getFacing() const {
    return facing;
}

void Player::vystrel() {
    if(pocetNabojov > 0) {
        pocetNabojov--;
    }
}

int Player::getPocetNabojov() const {
    return pocetNabojov;
}

void Player::naplnZbran() {
    this->pocetNabojov = 5;
}

void Player::setHp(int hp) {
    Player::hp = hp;
}

void Player::zasah() {
    if(this->hp > 0) {
        this->hp -= 10;
    }
}

int Player::getHp() const {
    return hp;
}

void Player::setFacing(Facing facing) {
    this->facing = facing;
}

int Player::getId() const {
    return id;
}

void Player::setId(int id) {
    Player::id = id;
}


