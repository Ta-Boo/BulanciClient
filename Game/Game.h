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
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture* background;
    SDL_Texture* koniecText[2];
    SDL_Texture* prekazka;
    SDL_Texture* playerText[PLAYERS_COUNT];
    SDL_Texture* bulletText[PLAYERS_COUNT];

    SDL_Rect srcR[PLAYERS_COUNT];
    SDL_Rect naboj, prekR;
    SDL_Rect playR[PLAYERS_COUNT];

    SDL_Point center;
    SDL_Point centerP;

    DataPlayer player;
    Player *players[PLAYERS_COUNT];
    Bullet *bullet[PLAYERS_COUNT];

    int pocitadlo = 0;
    bool leti = false;
    bool prvyRaz[PLAYERS_COUNT];
    int naboje[PLAYERS_COUNT];

    bool isRunning;

    void smerGulky(int i);
    void kontrolaGulky();
    int opacne(int i);

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
