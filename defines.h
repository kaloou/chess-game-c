#ifndef DEFINES_H
#define DEFINES_H

// Game Logic
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

// Move Types
#define MOVE_NORMAL 0
#define MOVE_ATTACK 1

// Window and Board
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SQUARE_SIZE 85
#define BOARD_X 0
#define BOARD_Y 0

// Colors
#define BG_COLOR_R 240
#define BG_COLOR_G 240
#define BG_COLOR_B 240

typedef struct {
    int row;
    int col;
    int type;
} Move;

#endif 