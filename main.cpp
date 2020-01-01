#include <SDL.h>
#include <iosfwd>
#include <sstream>
#include <iostream>
#include "SDL_image.h"
#include "Comunication/Message/Message.h"
#include "Comunication/Socket/Socket.h"




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


int main(int argc, char* argv[]) {

    DataPlayer player;
    player.possY =800;
    player.facing = top;
    player.possX = 600;
    player.hp = 80;
    Message message = Message();
    message.players[0] = player;
    message.players[1] = player;
    char* final = message.toString();
    return 0;
}