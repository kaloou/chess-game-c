#include "utils.h"
#include "game_graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces)
{
    for (int i = 1; i < 13; i++) {
        if (pieces.textures[i] != NULL)
            SDL_DestroyTexture(pieces.textures[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
} 