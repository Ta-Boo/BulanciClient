//
// Created by natalia on 1. 1. 2020.
//

#include <iostream>
#include "Game.h"
using namespace std;

SDL_Texture* playerText;
SDL_Rect srcR, destR;

Game::Game() {

    this->player1 = new Player(0,0);
    this->player2 = new Player(200,200);

}

Game::~Game() {

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
            SDL_SetRenderDrawColor(renderer, 50, 250, 50, 50);
            cout << "Renderer created" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    SDL_Surface* tmpSurface = player1->getImage();//IMG_Load("boat.jpg");
    playerText = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    cnt++;

    destR.h = 60;
    destR.w = 60;
    //destR.x = cnt % 640;
    const Uint8 *keystate;

    keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDLK_LEFT] ) {
        destR.x -= 2;
    }
    if (keystate[SDLK_RIGHT] ) {
        destR.x += 2;
    }
    if (keystate[SDLK_UP] ) {
        destR.y -= 2;
    }
    if (keystate[SDLK_DOWN] ) {
        destR.y += 2;
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
    cout << cnt << endl;
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerText, NULL, &destR);
    SDL_RenderPresent(renderer);

}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit;
    cout << "Game cleaned" << endl;
}

bool Game::running() {
    return isRunning;
}



