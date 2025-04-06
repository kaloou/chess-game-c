#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game_logic.h"
#include "game_graphics.h"

void game_loop(SDL_Renderer *renderer, ChessPieces pieces);
void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces);
void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces);

#endif 