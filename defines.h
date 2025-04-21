#ifndef DEFINES_H
#define DEFINES_H

enum ChessPiece {
    EMPTY = 0,
    W_PAWN = 1,
    W_KNIGHT = 2,
    W_BISHOP = 3,
    W_ROOK = 4,
    W_QUEEN = 5,
    W_KING = 6,
    B_PAWN = 7,
    B_KNIGHT = 8,
    B_BISHOP = 9,
    B_ROOK = 10,
    B_QUEEN = 11,
    B_KING = 12
};

#define BOARD_SIZE 8

#define WHITE true
#define BLACK false

// Move Types
#define MOVE_NORMAL 0
#define MOVE_ATTACK 1
#define MOVE_ILLEGAL 2
#define MOVE_CASTLE 3

// Window and Board
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SQUARE_SIZE 100
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

#define DEBUG_MODE false
#endif 