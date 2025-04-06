#include "game_logic.h"
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

bool turn = WHITE;



int get_moves(int row, int col, int **tab_moves)
{
    int size = 0;
    int piece = board[row][col];
    int knight_moves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    switch (piece) {
        case W_PAWN:
            if (is_empty(row - 1, col) && is_legal_move(row - 1, col)) {
                tab_moves[size][0] = row - 1;
                tab_moves[size][1] = col;
                size++;
            }
            if (row == 6 && is_empty(row - 2, col) && is_empty(row - 1, col) 
                && is_legal_move(row - 2, col)) {
                tab_moves[size][0] = row - 2;
                tab_moves[size][1] = col;
                size++;
            }
            if (has_enemy_piece(row - 1, col + 1, WHITE) && is_legal_move(row - 1, col + 1)) {
                tab_moves[size][0] = row - 1;
                tab_moves[size][1] = col + 1;
                size++;
            }
            if (has_enemy_piece(row - 1, col - 1, WHITE) && is_legal_move(row - 1, col - 1)) {
                tab_moves[size][0] = row - 1;
                tab_moves[size][1] = col - 1;
                size++;
            }
            break;

        case B_PAWN:
            // Même logique que W_PAWN mais vers le bas
            if (is_empty(row + 1, col) && is_legal_move(row + 1, col)) {
                tab_moves[size][0] = row + 1;
                tab_moves[size][1] = col;
                size++;
            }
            if (row == 1 && is_empty(row + 2, col) && is_empty(row + 1, col) 
                && is_legal_move(row + 2, col)) {
                tab_moves[size][0] = row + 2;
                tab_moves[size][1] = col;
                size++;
            }
            if (has_enemy_piece(row + 1, col + 1, BLACK) && is_legal_move(row + 1, col + 1)) {
                tab_moves[size][0] = row + 1;
                tab_moves[size][1] = col + 1;
                size++;
            }
            if (has_enemy_piece(row + 1, col - 1, BLACK) && is_legal_move(row + 1, col - 1)) {
                tab_moves[size][0] = row + 1;
                tab_moves[size][1] = col - 1;
                size++;
            }
            break;

        case W_KNIGHT:
        case B_KNIGHT:
            for (int i = 0; i < 8; i++) {
                int new_row = row + knight_moves[i][0];
                int new_col = col + knight_moves[i][1];
                if (is_legal_move(new_row, new_col) && 
                    (is_empty(new_row, new_col) || 
                     has_enemy_piece(new_row, new_col, piece <= W_KING ? WHITE : BLACK))) {
                    tab_moves[size][0] = new_row;
                    tab_moves[size][1] = new_col;
                    size++;
                }
            }
            break;
    }

    return size;
}

bool is_legal_move(int row, int col)
{
    if (!is_legal_position(row, col)) return false;
    return true;
}

void switch_turn(bool *turn)
{
    *turn = (*turn == WHITE) ? BLACK : WHITE;
}

bool is_legal_position(int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
} 
