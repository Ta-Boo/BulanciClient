//
// Created by natalia on 1. 1. 2020.
//
#include <zconf.h>
#include "Game.h"
using namespace std;



Game::Game() {

    players[0] = new Player(0,300);
    players[1] = new Player(740, 300);
    players[1]->update(0,0,LEFT);

    bullets[0] = new Bullet();
    bullets[1] = new Bullet();
    sendingThread = thread(&Game::sendStatus, this);
}

Game::~Game() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        delete players[i];
        delete bullets[i];
        SDL_DestroyTexture(playerText[i]);
        SDL_DestroyTexture(bulletText[i]);
    }
    //delete bullets;
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

        SDL_Surface* bulletSur = bullets[i]->getImage();//IMG_Load("bullets.png");
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
            players[0]->update(0, -3, TOP);
        }
        if (keys[SDL_SCANCODE_A]) {
            players[0]->update(-3, 0, LEFT);
        }
        if (keys[SDL_SCANCODE_S]) {
            players[0]->update(0, 3, BOT);
        }
        if (keys[SDL_SCANCODE_D]) {
            players[0]->update(3, 0, RIGHT);
        }
        if (keys[SDL_SCANCODE_SPACE] && !bullets[0]->isLeti()) {
            if(players[0]->getPocetNabojov() > 0) {
                if(!bullets[0]->isLeti()) {
                    bullets[0]->update(0, 0, players[0]->getFacing());
                    bullets[0]->setLeti(true);
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
                bullets[0]->setSurX(srcR[0].x);
                bullets[0]->setSurY(srcR[0].y);
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



    if(bullets[0]->isLeti() && prvyRaz[0]) {
        prvyRaz[0] = false;

    } else if (bullets[0]->isLeti() && !prvyRaz[0]){
        this->smerGulky(0);
        kontrolaGulky();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bulletText[0], nullptr, nullptr);


    if(players[0]->getHp() == 0)
    {
        SDL_RenderCopy(renderer, koniecText[0], nullptr, nullptr);

    } else if(players[1]->getHp() == 0)
    {
        SDL_RenderCopy(renderer, koniecText[1], nullptr, nullptr);
    } else {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
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
                if (bullets[i]->getFacing() == TOP) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 270, &center, SDL_FLIP_NONE);
                } else if (bullets[i]->getFacing() == RIGHT) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 0, &center, SDL_FLIP_NONE);
                } else if (bullets[i]->getFacing() == LEFT) {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 180, &center, SDL_FLIP_NONE);
                } else {
                    SDL_RenderCopyEx(renderer, bulletText[i], nullptr, &srcR[i], 90, &center, SDL_FLIP_NONE);
                }
            }
            SDL_RenderCopy(renderer, prekazka, nullptr, &prekR);
        }


    }

        SDL_RenderPresent(renderer);

}


bool Game::running() {
    return isRunning;
}

void Game::smerGulky(int i) {

    if(bullets[i]->getFacing() == TOP) {
        srcR[i].y -= 1;
        bullets[i]->update(0, -1, TOP);
    }
    if(bullets[i]->getFacing() == BOT) {
        srcR[i].y += 1;
        bullets[i]->update(0, 1, BOT);
    }
    if(bullets[i]->getFacing() == RIGHT) {
        srcR[i].x += 1;
        bullets[i]->update(1, 0, RIGHT);
    }
    if(bullets[i]->getFacing() == LEFT) {
        srcR[i].x -= 1;
        bullets[i]->update(-1, 0, LEFT);
    }
}
void Game::updateFromMessage(PlayerData message) {
    players[1]->setSurX(message.pX);
    players[1]->setSurY(message.pY);
    players[1]->setFacing(message.facing);

//    players[1]->update(message.players[1].pX, message.players[1].pY, message.players[1].facing);
//    players[0]->setHp(message.players[1].hp);

//    if(message.players[1].vystrelil) {
//        bullets[1]->update(0,0,players[0]->getFacing());
//        bullets[1]->setLeti(true);
//        players[1]->vystrel();
//        message.players[1].vystrelil = false;   //da sa poslat naspat?
//        prvyRaz[1] = true;
//        if(players[1]->getFacing() == RIGHT) {
//            srcR[1].y = playR[1].y + 40;
//            srcR[1].x = playR[1].x + 40;
//        } else if(players[1]->getFacing() == TOP){
//            srcR[1].y = playR[1].y;
//            srcR[1].x = playR[1].x + 40;
//        } else if(players[0]->getFacing() == BOT){
//            srcR[1].y = playR[1].y + 40;
//            srcR[1].x = playR[1].x + 10;
//        } else if(players[1]->getFacing() == LEFT){
//            srcR[1].y = playR[1].y + 10;
//            srcR[1].x = playR[1].x;
//        }
//    }

    bullets[1]->setSurX(srcR[1].x);
    bullets[1]->setSurY(srcR[1].y);

    if(bullets[1]->isLeti() && prvyRaz[1]) {
        prvyRaz[1] = false;

    } else if (bullets[1]->isLeti() && !prvyRaz[1]){
        this->smerGulky(1);
        kontrolaGulky();
    }
}

void Game::kontrolaGulky() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        if(srcR[i].x >= 800 || srcR[i].y >= 600 || srcR[i].x < 0-srcR[i].w || srcR[i].y < 0-srcR[i].h) {
            bullets[i]->setLeti(false);
        }
        if(srcR[i].x >= prekR.x +5 && srcR[i].y >= prekR.y + 5 && srcR[i].x <= prekR.w + prekR.x - 5 && srcR[i].y <= prekR.h + prekR.y - 5) {
            bullets[i]->setLeti(false);
            srcR[i].x = 800;
            srcR[i].y = 800;
        }
        if(bullets[i]->getSurX() >= players[!i]->getSurX() && bullets[i]->getSurX() <= players[!i]->getSurX() + playR[!i].w) {
            //bullets->setLeti(false);
            if(bullets[i]->getSurY() + 5 >= players[!i]->getSurY() && bullets[i]->getSurY() + 5 <= players[!i]->getSurY() + playR[!i].h) {
                bullets[i]->setLeti(false);
                srcR[i].x = 800;
                srcR[i].y = 800;
                players[!i]->zasah();
            }
        }
    }
}


bool Game::sendStatus() {
    sleep(1);
    while (true) {
        usleep(50000);
        _comunicationManager->sendMessage(getActualMessage());
        if(getActualMessage().exit) {
            break;
        }
    }
    sendingThread.detach();
    return true;
}

PlayerData Game::getActualMessage() {
    PlayerData message;
    message.facing = players[0]->getFacing();
    message.id = players[0]->getId();
    message.hp = players[0]->getHp();
    message.pX = players[0]->getSurX();
    message.pY = players[0]->getSurY();
    message.bulletFacing = bullets[0]->getFacing();
    message.bulletY = bullets[0]->getSurY();
    message.bulletX = bullets[0]->getSurX();
    message.exit = exit;
    return message;
}




