#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include "graphics.h"

#define WHITE true
#define BLACK false

extern bool turn;

void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces);
int get_moves(int row, int col, int **tab_moves);
bool is_legal_move(int row, int col);
void switch_turn(bool *turn);
void game_loop(SDL_Renderer *renderer, ChessPieces pieces);

#endif 