//
// Created by natalia on 30. 12. 2019.
//

#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include "Map.h"

Map::Map() {
    player1 = new Player;
    SDL_Surface * sur = player1->getImage();
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = IMG_Load("original.png"); //TODO zatial neviem ako dat lolalnu cestu treba fixnut zatial dajme absolutnu
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Texture * texture2 = SDL_CreateTextureFromSurface(renderer, sur);

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        //SDL_Rect dstrect = { 5, 5, 320, 240 };
        //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        //SDL_RenderCopy(renderer, sur, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
