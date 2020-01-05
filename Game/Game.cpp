//
// Created by natalia on 1. 1. 2020.
//
#include "Game.h"
#include "../Comunication/Message/Data/DataPlayer.h"

using namespace std;



Game::Game() {

    players[0] = new Player(0,0);
    players[1] = new Player(740, 0);
    players[1]->update(0,0,LEFT);

    this->bullet = new Bullet();
}

Game::~Game() {
    for(int i = 0; i < PLAYERS_COUNT; i++) {
        delete players[i];
    }
    delete bullet;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit;
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
    }
    SDL_Surface* bulletSur = bullet->getImage();//IMG_Load("bullet.png");
    bulletText = SDL_CreateTextureFromSurface(renderer, bulletSur);
    SDL_FreeSurface(bulletSur);

    srcR.w = 10;
    srcR.h = 10;

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
        if (keys[SDL_SCANCODE_SPACE] && !bullet->isLeti()) {
            if(players[0]->getPocetNabojov() > 0) {
                    if(!bullet->isLeti()) {
                        bullet->update(0,0,players[0]->getFacing());
                        bullet->setLeti(true);
                        players[0]->vystrel();
                }
                prvyRaz = true;
                if(players[0]->getFacing() == RIGHT) {
                    srcR.y = playR[0].y + 40;
                    srcR.x = playR[0].x + 40;
                } else if(players[0]->getFacing() == TOP){
                    srcR.y = playR[0].y;
                    srcR.x = playR[0].x + 40;
                } else if(players[0]->getFacing() == BOT){
                    srcR.y = playR[0].y + 40;
                    srcR.x = playR[0].x + 10;
                } else if(players[0]->getFacing() == LEFT){
                    srcR.y = playR[0].y + 10;
                    srcR.x = playR[0].x;
                }
                bullet->setSurX(srcR.x);
                bullet->setSurY(srcR.y);
            }

        }
    }
}

void Game::update() {
    if(players[0]->getHp() == 0)
    {
        //todo ukoncenie hry
    }
    if(players[0]->getPocetNabojov() == 0) {
        if (pocitadlo == 4000) {
            players[0]->naplnZbran();
            pocitadlo = 0;
        }
        pocitadlo++;
    }

    playR[0].x = players[0]->getSurX();
    playR[0].y = players[0]->getSurY();


    if(bullet->isLeti() && prvyRaz) {
        prvyRaz = false;

    } else if (bullet->isLeti() && !prvyRaz){
        this->smerGulky();
        kontrolaGulky();

    }

    if ( playR[0].x < 0 ) {
        playR[0].x = 0;
    }
    else if ( playR[0].x > 800-playR[0].w ) {
        playR[0].x = 800-playR[0].w;
    }
    if ( playR[0].y < 0 ) {
        playR[0].y = 0;
    }
    else if ( playR[0].y > 600-playR[0].h ) {
        playR[0].y = 600-playR[0].h;
    }

    Message messa = Message();
    messa.players[0].hp = players[0]->getHp();
    messa.players[0].possX = players[0]->getSurX();
    messa.players[0].possY = players[0]->getSurY();
    messa.players[0].facing = players[0]->getFacing();
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_RenderCopy(renderer, prekazka, nullptr, &prekR);


    for(int i = 0; i < PLAYERS_COUNT; i++) {
        if(players[i]->getFacing() == TOP) {
            SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 270, &centerP, SDL_FLIP_NONE);
        } else if(players[i]->getFacing() == RIGHT) {
            SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 0, &centerP, SDL_FLIP_NONE);
        } else if(players[i]->getFacing() == LEFT) {
            SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 180, &centerP, SDL_FLIP_NONE);
        } else if(players[i]->getFacing() == BOT){
            SDL_RenderCopyEx(renderer, playerText[i], nullptr, &playR[i], 90, &centerP, SDL_FLIP_NONE);
        }
        int x = 10 + 670*i;
        int y = 580;
        int j = 5 - players[i]->getPocetNabojov();
        for(int i = 0; i < 5 - j; i++) {

            naboj.w = 30;
            naboj.h = 30;
            naboj.x = x;
            naboj.y = y;
            x+=20;
            SDL_RenderCopyEx(renderer, bulletText, nullptr, &naboj, 270, &center, SDL_FLIP_NONE);
        }
    }

    if (bulletText != nullptr) {
        if(bullet->getFacing() == TOP) {
            SDL_RenderCopyEx(renderer, bulletText, nullptr, &srcR, 270, &center, SDL_FLIP_NONE);
        } else if(bullet->getFacing() == RIGHT) {
            SDL_RenderCopyEx(renderer, bulletText, nullptr, &srcR, 0, &center, SDL_FLIP_NONE);
        } else if(bullet->getFacing() == LEFT) {
            SDL_RenderCopyEx(renderer, bulletText, nullptr, &srcR, 180, &center, SDL_FLIP_NONE);
        } else {
            SDL_RenderCopyEx(renderer, bulletText, nullptr, &srcR, 90, &center, SDL_FLIP_NONE);
        }
    }
    SDL_RenderPresent(renderer);

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
void Game::updateFromMessage(Message message) {

    players[1]->update(message.players[1].possX, message.players[1].possY,message.players[1].facing);
    players[1]->setHp(message.players[1].hp);
}

void Game::kontrolaGulky() {
    if(srcR.x >= 800 || srcR.y >= 600 || srcR.x < 0-srcR.w || srcR.y < 0-srcR.h) {
        bullet->setLeti(false);
    }
    if(srcR.x >= prekR.x +5 && srcR.y >= prekR.y + 5 && srcR.x <= prekR.w + prekR.x - 5 && srcR.y <= prekR.h + prekR.y - 5) {
        bullet->setLeti(false);
        srcR.x = 800;
        srcR.y = 800;
    }
    if(bullet->getSurX() >= players[1]->getSurX() && bullet->getSurX() <= players[1]->getSurX() + playR[1].w) {
        //bullet->setLeti(false);
        if(bullet->getSurY() >= players[1]->getSurY() && bullet->getSurY() <= players[1]->getSurY() + playR[1].h) {
                bullet->setLeti(false);
                srcR.x = 800;
                srcR.y = 800;
                players[1]->zasah();
        }
    }

}




