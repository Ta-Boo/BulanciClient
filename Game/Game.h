//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_MAP_H
#define BULANCICLIENT_MAP_H

#include "SDL_image.h"
#include "Player.h"
#include "Bullet.h"

class Player;

class Game {
private:

    //Player *player1 = new Player(0,0);
    Player *player;
    Bullet *bullet;

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int cnt = 0;

    void smerGulky();

public:
    Game();
    virtual ~Game();

    void init(const char* title, int poX, int poY, int width, int height);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

};


#endif //BULANCICLIENT_MAP_H
