//
// Created by natalia on 1. 1. 2020.
//

#include <iostream>
#include "Game.h"
using namespace std;



//Facing facingBullet;



Game::Game() {

    //this->player1 = new Player(0,0);
    this->player = new Player(0,0);
    this->bullet = new Bullet();

}

Game::~Game() {
   delete player;
   delete bullet;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
//    SDL_FreeSurface(background);
    SDL_Quit;
    cout << "Game cleaned" << endl;
}

void Game::init(const char *title, int poX, int poY, int width, int height) {

    int flags = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Subsystems Initialised" << endl;

        window = SDL_CreateWindow(title, poX, poY, width, height, flags);
        if(window) {
            cout << "Window created" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_Surface* sur = IMG_Load("pozadie.jpeg");
            background = SDL_CreateTextureFromSurface(renderer, sur);
            SDL_FreeSurface(sur);
            //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            cout << "Renderer created" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }
    SDL_Surface *tmpSurface = player->getImage();
    playerText = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    //updatePlayerTexture();


}

void Game::handleEvents() {

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
            break;
        }
        if (keys[SDL_SCANCODE_W]) {
            player->update(0, -3, TOP);
        }
        if (keys[SDL_SCANCODE_A]) {
            player->update(-3, 0, LEFT);
        }
        if (keys[SDL_SCANCODE_S]) {
            player->update(0, 3, BOT);
        }
        if (keys[SDL_SCANCODE_D]) {
            player->update(3, 0, RIGHT);
        }
        if (keys[SDL_SCANCODE_SPACE]) {
            bullet->update(0,0,player->getFacing());
            leti = true;
            prvyRaz = true;
            if(player->getFacing() == RIGHT) {
                srcR.y = destR.y + 40;
                srcR.x = destR.x + 40;
            } else if(player->getFacing() == TOP){
                srcR.y = destR.y;
                srcR.x = destR.x + 40;
            } else if(player->getFacing() == BOT){
                srcR.y = destR.y + 40;
                srcR.x = destR.x + 10;
            } else if(player->getFacing() == LEFT){
                srcR.y = destR.y + 10;
                srcR.x = destR.x;
            }
            bullet->setSurX(srcR.x);
            bullet->setSurY(srcR.y);

        }
    }
}

void Game::update() {
    cnt++;

    destR.h = 60;
    destR.w = 60;


    srcR.w = 10;
    srcR.h = 10;

    center.x = 5;
    center.y = 5;

    centerP.x = destR.w/2;
    centerP.y = destR.h/2;

    destR.x = player->getSurX();
    destR.y = player->getSurY();

    //srcR.x = player->getSurX() + 40;
    //srcR.y = player->getSurX() + 40;

    if(leti && prvyRaz) {
        prvyRaz = false;

        SDL_Surface* bullet = IMG_Load("bullet.png");
        bulletText = SDL_CreateTextureFromSurface(renderer, bullet);
        SDL_FreeSurface(bullet);

    } else if (leti && !prvyRaz){
        this->smerGulky();
        //prvyRaz = false;
        if(srcR.x >= 800 || srcR.y >= 600) {
            leti = false;
            //srcR.y = destR.y + 800;
            //bullet->update(0,srcR.y + 800,bullet->getFacing());
            //bullet->update(srcR.x + 800,0,bullet->getFacing());
            //srcR.x = destR.x + 800;
        }
    }

    if ( destR.x < 0 ) {
        destR.x = 0;
    }
    else if ( destR.x > 800-destR.w ) {
        destR.x = 800-destR.w;
    }
    if ( destR.y < 0 ) {
        destR.y = 0;
    }
    else if ( destR.y > 600-destR.h ) {
        destR.y = 600-destR.h;
    }


}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    //SDL_RenderCopy(renderer, playerText, NULL, &destR);
    //SDL_RenderCopy(renderer, bulletText, NULL, &srcR);
    if(player->getFacing() == TOP) {
        SDL_RenderCopyEx(renderer, playerText, NULL, &destR, 270, &centerP, SDL_FLIP_NONE);
    } else if(player->getFacing() == RIGHT) {
        SDL_RenderCopyEx(renderer, playerText, NULL, &destR, 0, &centerP, SDL_FLIP_NONE);
    } else if(player->getFacing() == LEFT) {
        SDL_RenderCopyEx(renderer, playerText, NULL, &destR, 180, &centerP, SDL_FLIP_NONE);
    } else {
        SDL_RenderCopyEx(renderer, playerText, NULL, &destR, 90, &centerP, SDL_FLIP_NONE);
    }
    if (bulletText) {
        if(bullet->getFacing() == TOP) {
            SDL_RenderCopyEx(renderer, bulletText, NULL, &srcR, 270, &center, SDL_FLIP_NONE);
        } else if(bullet->getFacing() == RIGHT) {
            SDL_RenderCopyEx(renderer, bulletText, NULL, &srcR, 0, &center, SDL_FLIP_NONE);
        } else if(bullet->getFacing() == LEFT) {
            SDL_RenderCopyEx(renderer, bulletText, NULL, &srcR, 180, &center, SDL_FLIP_NONE);
        } else {
            SDL_RenderCopyEx(renderer, bulletText, NULL, &srcR, 90, &center, SDL_FLIP_NONE);
        }
    }
    SDL_RenderPresent(renderer);

}

void Game::clean() {

}

bool Game::running() {
    return isRunning;
}

void Game::smerGulky() {

    if(bullet->getFacing() == TOP) {
        srcR.y -= 1;
        bullet->update(0,-1,TOP);
    }
    if(bullet->getFacing() == BOT) {
        srcR.y += 1;
        bullet->update(0,1,BOT);
    }
    if(bullet->getFacing() == RIGHT) {
        srcR.x += 1;
        bullet->update(1,0,RIGHT);
    }
    if(bullet->getFacing() == LEFT) {
        srcR.x -= 1;
        bullet->update(-1,0,LEFT);
    }
}




