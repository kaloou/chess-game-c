#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include "game_graphics.h"

#define BOARD_SIZE 8
#define EMPTY 0
#define W_PAWN 1
#define W_KNIGHT 2
#define W_BISHOP 3
#define W_ROOK 4
#define W_QUEEN 5
#define W_KING 6
#define B_PAWN 7
#define B_KNIGHT 8
#define B_BISHOP 9
#define B_ROOK 10
#define B_QUEEN 11
#define B_KING 12

#define WHITE true
#define BLACK false

extern bool turn;
extern int board[BOARD_SIZE][BOARD_SIZE];

void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces);
int get_moves(int row, int col, int **tab_moves);
bool is_legal_move(int row, int col);
void switch_turn(bool *turn);
void game_loop(SDL_Renderer *renderer, ChessPieces pieces);
void initialize_board(void);
bool is_empty(int row, int col);
bool has_enemy_piece(int row, int col, bool is_white);
bool is_legal_position(int row, int col);

#endif 