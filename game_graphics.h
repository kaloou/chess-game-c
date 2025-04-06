#ifndef GAME_GRAPHICS_H
#define GAME_GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600
#define SQUARE_SIZE (BOARD_WIDTH / BOARD_SIZE)
#define BOARD_X ((WINDOW_WIDTH - BOARD_WIDTH) / 2)
#define BOARD_Y ((WINDOW_HEIGHT - BOARD_HEIGHT) / 2)
#define BG_COLOR_R 200
#define BG_COLOR_G 200
#define BG_COLOR_B 200

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
void show_moves(SDL_Renderer *renderer, int **tab_moves, int size);


#endif 