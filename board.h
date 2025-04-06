#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

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

extern int board[BOARD_SIZE][BOARD_SIZE];

void initialize_board(void);
bool is_empty(int row, int col);
bool has_enemy_piece(int row, int col, bool is_white);

#endif 