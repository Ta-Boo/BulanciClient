//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_MAP_H
#define BULANCICLIENT_MAP_H

#include "SDL_image.h"

#include "Player.h"



class Game {
private:
    Player *player1;
    Player *player2;

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int cnt = 0;

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
