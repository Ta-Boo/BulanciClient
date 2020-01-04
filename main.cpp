#include <SDL.h>

#include "Comunication/Message/Message.h"
#include "Game/Game.h"
#include "Comunication/ComunicationManager/ComunicationManager.h"

int main(int argc, char* argv[]) {
    Game game;
    game.init("tf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
    while (game.running()){
        game.handleEvents();
        game.update();
        game.render();
    }
    game.clean();

//    ComunicationManager manager;
//    manager.connectSocket(argv[1],atoi(argv[2]));
//    Message mess;
//    manager.activateListening();


    //delete game;
    return 0;
}