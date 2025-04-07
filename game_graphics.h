#ifndef GAME_GRAPHICS_H
#define GAME_GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defines.h"

typedef struct {
    SDL_Texture *textures[13];
} ChessPieces;

int init_sdl(void);
SDL_Window *create_window(void);
SDL_Renderer *create_renderer(SDL_Window *window);
void draw_background(SDL_Renderer *renderer);
void draw_board(SDL_Renderer *renderer);
ChessPieces load_chess_pieces(SDL_Renderer *renderer);
void draw_pieces(SDL_Renderer *renderer, ChessPieces pieces);
void show_moves(SDL_Renderer *renderer, Move *moves, int size);

#endif 