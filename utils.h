#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game_logic.h"
#include "game_graphics.h"

extern bool waiting_for_move;
extern int selected_row, selected_col;
extern Move *possible_moves;
extern int moves_size;

void reset_params(void);
void reset_moves(void);
void display_moves(SDL_Renderer *renderer, ChessPieces pieces);
bool handle_first_click(int row, int col);
bool handle_second_click(int row, int col);
void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces);
void game_loop(SDL_Renderer *renderer, ChessPieces pieces);
void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces);
void switch_turn(void);

#endif 