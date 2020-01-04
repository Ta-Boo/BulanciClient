//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_MAP_H
#define BULANCICLIENT_MAP_H

#include "SDL_image.h"
#include "Player.h"
#include "Bullet.h"
#include "../Comunication/Message/Message.h"
#include "../Comunication/Message/Data/DataPlayer.h"

#include <iostream>

#define PLAYERS_COUNT 2
//#include "../Comunication/Message/Message.h"

class Player;

class Game {
private:
    DataPlayer player;
    //Player *player1 = new Player(0,0);
    //Player *player;
    //Player *enemy;
    Player *players[PLAYERS_COUNT];

    Bullet *bullet;
    bool leti = false;
    bool prvyRaz = true;
    SDL_Texture* background;
    SDL_Texture* playerText[PLAYERS_COUNT];
    int naboje[PLAYERS_COUNT];
    //SDL_Texture* enemyText;

    SDL_Rect srcR, naboj;
    SDL_Rect playR[PLAYERS_COUNT];

    SDL_Point center;
    SDL_Point centerP;
    SDL_Texture* bulletText;


    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int cnt = 0;

    void smerGulky();

public:
    Game();
    ~Game();

    void init(const char* title, int poX, int poY, int width, int height);

    void handleEvents();
    void update();
    void updateFromMessage(Message message);
    void render();

    bool running();

};


#endif //BULANCICLIENT_MAP_H
