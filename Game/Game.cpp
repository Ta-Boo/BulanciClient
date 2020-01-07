//
// Created by natalia on 1. 1. 2020.
//
#include <zconf.h>
#include "Game.h"
#include "../Comunication/Message/Data/DataPlayer.h"
using namespace std;



Game::Game() {

    players[0] = new Player(0,300);
    players[1] = new Player(740, 300);
    players[1]->update(0,0,LEFT);

    bullet[0] = new Bullet();
    bullet[1] = new Bullet();
}

Game::~Game() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        delete players[i];
        delete bullet[i];
        SDL_DestroyTexture(playerText[i]);
        SDL_DestroyTexture(bulletText[i]);
    }
    //delete bullet;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(prekazka);
    //SDL_DestroyTexture(bulletText);
    for(int i = 0; i < 2; i++) {
        SDL_DestroyTexture(koniecText[i]);
    }
    SDL_Quit();
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

            SDL_Surface* prek = IMG_Load("prekazka.png");
            prekazka = SDL_CreateTextureFromSurface(renderer, prek);
            SDL_FreeSurface(prek);
            prekR.w = 200;
            prekR.h = 200;
            prekR.x = 400 - 100;
            prekR.y = 300 - 100;
            cout << "Renderer created" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    for(int i = 0; i < PLAYERS_COUNT; i++) {
        SDL_Surface *tmpSurface = players[i]->getImage();
        playerText[i] = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        playR[i].h = 60;
        playR[i].w = 60;
        playR[i].x = players[i]->getSurX();
        playR[i].y = players[i]->getSurY();
        naboje[i] = players[i]->getPocetNabojov();

        SDL_Surface* bulletSur = bullet[i]->getImage();//IMG_Load("bullet.png");
        bulletText[i] = SDL_CreateTextureFromSurface(renderer, bulletSur);
        SDL_FreeSurface(bulletSur);

        srcR[i].w = 10;
        srcR[i].h = 10;

    }

    SDL_Surface* koniec = IMG_Load("gameOver.jpeg");
    koniecText[0] = SDL_CreateTextureFromSurface(renderer, koniec);
    SDL_FreeSurface(koniec);

    SDL_Surface* koniec1 = IMG_Load("win.jpeg");
    koniecText[1] = SDL_CreateTextureFromSurface(renderer, koniec1);
    SDL_FreeSurface(koniec1);

    center.x = 5;
    center.y = 5;

    centerP.x = playR[0].w/2;
    centerP.y = playR[0].h/2;

}

void Game::handleEvents() {

    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
            break;
        }
        if (keys[SDL_SCANCODE_W]) {
            if(players[0]->getSurX() >= prekR.x && players[0]->getSurY() > prekR.y && players[0]->getSurX() <= prekR.x + prekR.w && players[0]->getSurY() <= prekR.y + prekR.h) {
                    players[0]->update(0, 0, TOP);
            } else {
                players[0]->update(0, -3, TOP);
            }
        }
        if (keys[SDL_SCANCODE_A]) {
            if(players[0]->getSurX() <= prekR.x + prekR.w && players[0]->getSurX() > prekR.x && players[0]->getSurY() <= prekR.y + prekR.h && players[0]->getSurY() >= prekR.y) {
                players[0]->update(0, 0, LEFT);
            } else {
                players[0]->update(-3, 0, LEFT);
            }
            //players[0]->update(-3, 0, LEFT);
        }
        if (keys[SDL_SCANCODE_S]) {
            if(players[0]->getSurX() >= prekR.x && players[0]->getSurX() <= prekR.x + prekR.w && players[0]->getSurY() + playR[0].h >= prekR.y && players[0]->getSurY() < prekR.y + prekR.h) {
                players[0]->update(0, 0, BOT);
            } else {
                players[0]->update(0, 3, BOT);
            }
            //players[0]->update(0, 3, BOT);
        }
        if (keys[SDL_SCANCODE_D]) {
            players[0]->update(3, 0, RIGHT);
        }
        if (keys[SDL_SCANCODE_SPACE] && !bullet[0]->isLeti()) {
            if(players[0]->getPocetNabojov() > 0) {
                if(!bullet[0]->isLeti()) {
                    bullet[0]->update(0,0,players[0]->getFacing());
                    bullet[0]->setLeti(true);
                    players[0]->vystrel();
                }
                prvyRaz[0] = true;
                if(players[0]->getFacing() == RIGHT) {
                    srcR[0].y = playR[0].y + 40;
                    srcR[0].x = playR[0].x + 40;
                } else if(players[0]->getFacing() == TOP){
                    srcR[0].y = playR[0].y;
                    srcR[0].x = playR[0].x + 40;
                } else if(players[0]->getFacing() == BOT){
                    srcR[0].y = playR[0].y + 40;
                    srcR[0].x = playR[0].x + 10;
                } else if(players[0]->getFacing() == LEFT){
                    srcR[0].y = playR[0].y + 10;
                    srcR[0].x = playR[0].x;
                }
                bullet[0]->setSurX(srcR[0].x);
                bullet[0]->setSurY(srcR[0].y);
            }

        }
    }
}
void Game::reload() {

    sleep(4);
    players[0]->naplnZbran();
    reloading = false;
    reloadingThread.detach();
}

void Game::update() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        if(players[0]->getPocetNabojov() == 0) {
            if (!reloading) {
                reloading = true;
                reloadingThread = thread(&Game::reload, this);
            }

        }
        playR[i].x = players[i]->getSurX();
        playR[i].y = players[i]->getSurY();

        if ( playR[i].x < 0 ) {
            playR[i].x = 0;
        }
        else if ( playR[i].x > 800-playR[i].w ) {
            playR[i].x = 800-playR[i].w;
        }
        if ( playR[i].y < 0 ) {
            playR[i].y = 0;
        }
        else if ( playR[i].y > 600-playR[i].h ) {
            playR[i].y = 600-playR[i].h;
        }
    }

    Message messa = Message();
    messa.players[0].hp = players[1]->getHp();     // posielat superove HP? o.O
    messa.players[0].possX = players[0]->getSurX();
    messa.players[0].possY = players[0]->getSurY();
    messa.players[0].facing = players[0]->getFacing();

    if(bullet[0]->isLeti() && prvyRaz[0]) {
        messa.players[0].vystrelil = true;
        prvyRaz[0] = false;

    } else if (bullet[0]->isLeti() && !prvyRaz[0]){
        this->smerGulky(0);
        kontrolaGulky();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);


    if(players[0]->getHp() == 0)
    {
        SDL_RenderCopy(renderer, koniecText[0], nullptr, nullptr);

    } else if(players[1]->getHp() == 0)
    {
        SDL_RenderCopy(renderer, koniecText[1], nullptr, nullptr);
    } else {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
        SDL_RenderCopy(renderer, prekazka, nullptr, &prekR);
    }
        for (int i = 0; i < PLAYERS_COUNT; i++) {
            if (players[i]->getFacing() == TOP) {
                SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 270, &centerP, SDL_FLIP_NONE);
            } else if (players[i]->getFacing() == RIGHT) {
                SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 0, &centerP, SDL_FLIP_NONE);
            } else if (players[i]->getFacing() == LEFT) {
                SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 180, &centerP, SDL_FLIP_NONE);
            } else if (players[i]->getFacing() == BOT) {
                SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 90, &centerP, SDL_FLIP_NONE);
            }
            int x = 10 + 670 * i;
            int y = 580;
            int j = 5 - players[i]->getPocetNabojov();
            for (int i = 0; i < 5 - j; i++) {

                naboj.w = 30;
                naboj.h = 30;
                naboj.x = x;
                naboj.y = y;
                x += 20;
                SDL_RenderCopyEx(renderer, bulletText[0], nullptr, &naboj, 270, &center, SDL_FLIP_NONE);
            }

            if (bulletText[i] != nullptr) {
                if (bullet[i]->getFacing() == TOP) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 270, &center, SDL_FLIP_NONE);
                } else if (bullet[i]->getFacing() == RIGHT) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 0, &center, SDL_FLIP_NONE);
                } else if (bullet[i]->getFacing() == LEFT) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 180, &center, SDL_FLIP_NONE);
                } else {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 90, &center, SDL_FLIP_NONE);
                }
            }
        }


        SDL_RenderPresent(renderer);

}


bool Game::running() {
    return isRunning;
}

void Game::smerGulky(int i) {

    if(bullet[i]->getFacing() == TOP) {
        srcR[i].y -= 1;
        bullet[i]->update(0,-1,TOP);
    }
    if(bullet[i]->getFacing() == BOT) {
        srcR[i].y += 1;
        bullet[i]->update(0,1,BOT);
    }
    if(bullet[i]->getFacing() == RIGHT) {
        srcR[i].x += 1;
        bullet[i]->update(1,0,RIGHT);
    }
    if(bullet[i]->getFacing() == LEFT) {
        srcR[i].x -= 1;
        bullet[i]->update(-1,0,LEFT);
    }
}
void Game::updateFromMessage(Message message) {

    players[1]->update(message.players[1].possX, message.players[1].possY,message.players[1].facing);
//    players[0]->setHp(message.players[1].hp);

    if(message.players[1].vystrelil) {
        bullet[1]->update(0,0,players[0]->getFacing());
        bullet[1]->setLeti(true);
        players[1]->vystrel();
        message.players[1].vystrelil = false;   //da sa poslat naspat?
        prvyRaz[1] = true;
        if(players[1]->getFacing() == RIGHT) {
            srcR[1].y = playR[1].y + 40;
            srcR[1].x = playR[1].x + 40;
        } else if(players[1]->getFacing() == TOP){
            srcR[1].y = playR[1].y;
            srcR[1].x = playR[1].x + 40;
        } else if(players[0]->getFacing() == BOT){
            srcR[1].y = playR[1].y + 40;
            srcR[1].x = playR[1].x + 10;
        } else if(players[1]->getFacing() == LEFT){
            srcR[1].y = playR[1].y + 10;
            srcR[1].x = playR[1].x;
        }
    }

    bullet[1]->setSurX(srcR[1].x);
    bullet[1]->setSurY(srcR[1].y);

    if(bullet[1]->isLeti() && prvyRaz[1]) {
        prvyRaz[1] = false;

    } else if (bullet[1]->isLeti() && !prvyRaz[1]){
        this->smerGulky(1);
        kontrolaGulky();
    }
}

void Game::kontrolaGulky() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        if(srcR[i].x >= 800 || srcR[i].y >= 600 || srcR[i].x < 0-srcR[i].w || srcR[i].y < 0-srcR[i].h) {
            bullet[i]->setLeti(false);
        }
        if(srcR[i].x >= prekR.x +5 && srcR[i].y >= prekR.y + 5 && srcR[i].x <= prekR.w + prekR.x - 5 && srcR[i].y <= prekR.h + prekR.y - 5) {
            bullet[i]->setLeti(false);
            srcR[i].x = 800;
            srcR[i].y = 800;
        }
        if(bullet[i]->getSurX() >= players[opacne(i)]->getSurX() && bullet[i]->getSurX() <= players[opacne(i)]->getSurX() + playR[opacne(i)].w) {
            //bullet->setLeti(false);
            if(bullet[i]->getSurY() >= players[opacne(i)]->getSurY() && bullet[i]->getSurY() <= players[opacne(i)]->getSurY() + playR[opacne(i)].h) {
                bullet[i]->setLeti(false);
                srcR[i].x = 800;
                srcR[i].y = 800;
                players[opacne(i)]->zasah();
            }
        }
    }
}

int Game::opacne(int i) {
    if(i == 0) {
        return 1;
    } else {
        return 0;
    }
}

bool Game::sendStatus(Message* message) {
    _comunicationManager->sendMessage(message);
    return true;
}




