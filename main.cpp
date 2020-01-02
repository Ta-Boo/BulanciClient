#include <SDL.h>
#include <iosfwd>
#include <sstream>
#include <iostream>
#include "SDL_image.h"
#include "Comunication/Message/Message.h"
#include "Comunication/Socket/Socket.h"
#include "Game/Game.h"




//int main(int argc, char ** argv)
//{
//    bool quit = false;
//    SDL_Event event;
//
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
//                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
//
//    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
//    SDL_Surface * image = IMG_Load("original.png");
//    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
//
//    while (!quit)
//    {
//        SDL_WaitEvent(&event);
//
//        switch (event.type)
//        {
//            case SDL_QUIT:
//                quit = true;
//                break;
//        }
//
//        //SDL_Rect dstrect = { 5, 5, 320, 240 };
//        //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
//        SDL_RenderCopy(renderer, texture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//    }
//
//    SDL_DestroyTexture(texture);
//    SDL_FreeSurface(image);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//
//    SDL_Quit();
//
//    return 0;
//}

Game *game = nullptr;


int main(int argc, char* argv[]) {
    game = new Map;
    game->init("tf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
    while (game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    Socket socket = Socket();
    socket.connectSocket(argv[1],atoi(argv[2]));
//    socket.sendMessage();
    socket.listenForMessages();




    return 0;
}