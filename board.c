#include "board.h"
#include "utils.h"

int board[BOARD_SIZE][BOARD_SIZE];

void initialize_board(void)
{
    board[0][0] = B_ROOK;
    board[0][1] = B_KNIGHT;
    board[0][2] = B_BISHOP;
    board[0][3] = B_QUEEN;
    board[0][4] = B_KING;
    board[0][5] = B_BISHOP;
    board[0][6] = B_KNIGHT;
    board[0][7] = B_ROOK;
    
    for (int col = 0; col < BOARD_SIZE; col++)
        board[1][col] = B_PAWN;
    
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < BOARD_SIZE; col++)
            board[row][col] = EMPTY;
    }
    
    for (int col = 0; col < BOARD_SIZE; col++)
        board[6][col] = W_PAWN;
    
    board[7][0] = W_ROOK;
    board[7][1] = W_KNIGHT;
    board[7][2] = W_BISHOP;
    board[7][3] = W_QUEEN;
    board[7][4] = W_KING;
    board[7][5] = W_BISHOP;
    board[7][6] = W_KNIGHT;
    board[7][7] = W_ROOK;
}

bool is_empty(int row, int col)
{
    if (!is_legal_position(row, col)) return false;
    return board[row][col] == EMPTY;
}

bool has_enemy_piece(int row, int col, bool is_white)
{
    if (!is_legal_position(row, col)) return false;
    
    int piece = board[row][col];
    if (is_white)
        return (piece >= B_PAWN && piece <= B_KING);
    else
        return (piece >= W_PAWN && piece <= W_KING);
} 