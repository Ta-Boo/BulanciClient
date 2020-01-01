//
// Created by natalia on 30. 12. 2019.
//

#include "Player.h"

Player::Player() {
    image = IMG_Load("bulanko.png");
    surX = 0;
    surY = 0;
}

void Player::pohyb() {
    const Uint8 *keystate;

    keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDLK_LEFT] ) {
         surX -= 2;
    }
    if (keystate[SDLK_RIGHT] ) {
        surX += 2;
    }
    if (keystate[SDLK_UP] ) {
        surY -= 2;
    }
    if (keystate[SDLK_DOWN] ) {
        surY += 2;
    }
    /* collide with edges of screen */
    /*if ( x < 0 ) {
        x = 0;
    }
    else if ( x > SCREEN_WIDTH-SPRITE_SIZE ) {
        x = SCREEN_WIDTH-SPRITE_SIZE;
    }
    if ( y < 0 ) {
        y = 0;
    }
    else if ( y > SCREEN_HEIGHT-SPRITE_SIZE ) {
        y = SCREEN_HEIGHT-SPRITE_SIZE;
    }*/
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

SDL_Surface *Player::getImage() const {
    return image;
}
