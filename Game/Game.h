//
// Created by natalia on 1. 1. 2020.
//

#ifndef BULANCICLIENT_MAP_H
#define BULANCICLIENT_MAP_H

#include "SDL_image.h"
#include "Player.h"
#include "Bullet.h"
#include "../Comunication/ComunicationManager/ComunicationManager.h"

#include <iostream>
#include <thread>

#define PLAYERS_COUNT 2

class Player;

class Game {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture* background;
    SDL_Texture* koniecText[2];
    SDL_Texture* prekazka;
    SDL_Texture* palickaTx;
    SDL_Texture* playerText[PLAYERS_COUNT];
    SDL_Texture* bulletText[PLAYERS_COUNT];

    SDL_Rect srcR[PLAYERS_COUNT];
    SDL_Rect naboj, palR, prekR;
    SDL_Rect playR[PLAYERS_COUNT];

    SDL_Point center;
    SDL_Point centerP;

    Player *players[PLAYERS_COUNT];
    Bullet *bullets[PLAYERS_COUNT];
    int exit = 0;

    bool    reloading = false;
    bool    prvyRaz[PLAYERS_COUNT];
    int     naboje[PLAYERS_COUNT];

    bool isRunning;

    void smerGulky(int i);
    void kontrolaGulky();

    thread reloadingThread;
    void reload();
    thread sendingThread;
    PlayerData getActualMessage();
    bool sendStatus();
public:
    ComunicationManager* _comunicationManager;

    Game();

    ~Game();
    void init(const char* title, int poX, int poY, int width, int height);
    void handleEvents();
    void update();
    void updateFromMessage(PlayerData message);

    void render();
    bool running();

};


#endif //BULANCICLIENT_MAP_H
