#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include "defines.h"

extern bool turn;
extern int board[BOARD_SIZE][BOARD_SIZE];
extern bool white_king_moved;
extern bool black_king_moved;
extern bool white_rook_left_moved;
extern bool white_rook_right_moved;
extern bool black_rook_left_moved;
extern bool black_rook_right_moved;

int get_moves(int row, int col, Move **moves, bool option);
bool is_valid_move(int row, int col, int old_row, int old_col);
void initialize_board(void);
bool is_empty(int row, int col);
bool is_enemy_piece(int row, int col, bool option);
bool get_color(int row, int col);
bool is_on_board(int row, int col);
bool is_in_check(bool color);
void remove_illegal_moves(int row, int col, Move **moves, int size);
bool is_checkmate(bool color);
bool can_block_check(bool color);
bool can_castle(bool color, bool kingside);

#endif 