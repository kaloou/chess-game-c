#include "game_logic.h"
#include "utils.h"

bool turn = WHITE;

//----------------
// BOARD FUNCTIONS
//----------------
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
    /*
    for (int col = 0; col < BOARD_SIZE; col++)
        board[6][col] = W_PAWN;
    */
    
    board[7][0] = W_ROOK;
    board[7][1] = W_KNIGHT;
    board[7][2] = W_BISHOP;
    board[7][3] = W_QUEEN;
    board[7][4] = W_KING;
    board[7][5] = W_BISHOP;
    board[7][6] = W_KNIGHT;
    board[7][7] = W_ROOK;
}


//---------------
// GET FUNCTIONS
//---------------

int get_moves(int row, int col, Move **moves)
{
    int size = 0;
    int piece = board[row][col];

    switch (piece) {
        case W_PAWN:
            if (is_empty(row - 1, col) && is_legal_move(row - 1, col)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (row == 6 && is_empty(row - 2, col) && is_empty(row - 1, col) 
                && is_legal_move(row - 2, col)) {
                (*moves)[size].row = row - 2;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (is_enemy_piece(row - 1, col + 1) && is_legal_move(row - 1, col + 1)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col + 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            if (is_enemy_piece(row - 1, col - 1) && is_legal_move(row - 1, col - 1)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col - 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            break;

        case B_PAWN:
            if (is_empty(row + 1, col) && is_legal_move(row + 1, col)) {
                (*moves)[size].row = row + 1;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (row == 1 && is_empty(row + 2, col) && is_empty(row + 1, col) 
                && is_legal_move(row + 2, col)) {
                (*moves)[size].row = row + 2;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (is_enemy_piece(row + 1, col + 1) && is_legal_move(row + 1, col + 1)) {
                (*moves)[size].row = row + 1;
                (*moves)[size].col = col + 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            if (is_enemy_piece(row + 1, col - 1) && is_legal_move(row + 1, col - 1)) {
                (*moves)[size].row = row + 1;
                (*moves)[size].col = col - 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            break;

        case W_KNIGHT:
        case B_KNIGHT:
        {
            int knight_moves[8][2] = {
                {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                {1, -2}, {1, 2}, {2, -1}, {2, 1}
            };
            for (int i = 0; i < 8; i++) {
                int new_row = row + knight_moves[i][0];
                int new_col = col + knight_moves[i][1];
                if (is_legal_move(new_row, new_col)) {
                    if (is_empty(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                    }
                }
            }
            break;
        }

        case W_ROOK:
        case B_ROOK:
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col)) {
                    if (is_empty(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                // Vers le bas
                if (is_legal_move(row + i, col)) {
                    if (is_empty(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row, col - i)) {
                    if (is_empty(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row, col + i)) {
                    if (is_empty(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            break;

        case W_BISHOP:
        case B_BISHOP:
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col - i)) {
                    if (is_empty(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col + i)) {
                    if (is_empty(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row + i, col - i)) {
                    if (is_empty(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row + i, col + i)) {
                    if (is_empty(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            break;

        case W_QUEEN:
        case B_QUEEN:
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col)) {
                    if (is_empty(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row + i, col)) {
                    if (is_empty(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row, col - i)) {
                    if (is_empty(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row, col + i)) {
                    if (is_empty(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col - i)) {
                    if (is_empty(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row - i, col + i)) {
                    if (is_empty(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row + i, col - i)) {
                    if (is_empty(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_legal_move(row + i, col + i)) {
                    if (is_empty(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            break;

        case W_KING:
        case B_KING:
        {
            int king_moves[8][2] = {
                {-1, -1}, {-1, 0}, {-1, 1},
                {0, -1},           {0, 1},
                {1, -1},  {1, 0},  {1, 1}
            };
            for (int i = 0; i < 8; i++) {
                int new_row = row + king_moves[i][0];
                int new_col = col + king_moves[i][1];
                if (is_legal_move(new_row, new_col)) {
                    if (is_empty(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                    }
                }
            }
            break;
        }
    }

    *moves = realloc(*moves, size * sizeof(Move));
    if (*moves == NULL && size > 0) {
        fprintf(stderr, "Erreur de réallocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    return size;
}

bool get_color(int row, int col)
{
    int piece = board[row][col];
    if (piece >= W_PAWN && piece <= W_KING)
        return WHITE;
    else if (piece >= B_PAWN && piece <= B_KING) 
        return BLACK;
    return WHITE;
}

//------------------
// CHECKS FUNCTIONS
//------------------
bool is_legal_move(int row, int col)
{
    if (!is_on_board(row, col)) return false;
    return true;
}

bool is_empty(int row, int col)
{
    if (!is_on_board(row, col)) return false;
    return board[row][col] == EMPTY;
}

bool is_enemy_piece(int row, int col)
{
    if (!is_on_board(row, col)) return false;
    
    int piece = board[row][col];
    if (piece == EMPTY) return false;
    
    bool selected_piece_color = get_color(row, col);
    bool current_turn = turn;
    
    return selected_piece_color != current_turn;
}

bool is_on_board(int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
} 
