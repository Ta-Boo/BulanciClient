#include <SDL.h>

#include "Comunication/Message/Message.h"
#include "Game/Game.h"
#include "Comunication/ComunicationManager/ComunicationManager.h"

int main(int argc, char* argv[]) {
    ComunicationManager comunicationManager;
//    comunicationManager.connectSocket(argv[1],atoi(argv[2]));
    Game game;
    game._comunicationManager = &comunicationManager;
//    comunicationManager.activateListening(&game);


    game.init("bulanci", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
    while (game.running()){
        game.handleEvents();
        game.update();
        game.render();
    }
//    comunicationManager.waitForFinish();
    return 0;
}