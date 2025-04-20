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

//----------------
// MOVE FUNCTIONS
//----------------
int get_moves(int row, int col, Move **moves, bool option)
{
    *moves = malloc(27 * sizeof(Move));
    if (moves == NULL){
        fprintf(stdout, "Erreur d'allocation mémoire\n");
        return 1;
    }

    int size = 0;
    int piece = board[row][col];

    switch (piece) {
        case W_PAWN:
            if (is_empty(row - 1, col) && is_on_board(row - 1, col)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (row == 6 && is_empty(row - 2, col) && is_empty(row - 1, col) 
                && is_on_board(row - 2, col)) {
                (*moves)[size].row = row - 2;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (is_enemy_piece(row - 1, col + 1, option) && is_on_board(row - 1, col + 1)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col + 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            if (is_enemy_piece(row - 1, col - 1, option) && is_on_board(row - 1, col - 1)) {
                (*moves)[size].row = row - 1;
                (*moves)[size].col = col - 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            break;

        case B_PAWN:
            if (is_empty(row + 1, col) && is_on_board(row + 1, col)) {
                (*moves)[size].row = row + 1;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (row == 1 && is_empty(row + 2, col) && is_empty(row + 1, col) 
                && is_on_board(row + 2, col)) {
                (*moves)[size].row = row + 2;
                (*moves)[size].col = col;
                (*moves)[size].type = MOVE_NORMAL;
                size++;
            }
            if (is_enemy_piece(row + 1, col + 1, option) && is_on_board(row + 1, col + 1)) {
                (*moves)[size].row = row + 1;
                (*moves)[size].col = col + 1;
                (*moves)[size].type = MOVE_ATTACK;
                size++;
            }
            if (is_enemy_piece(row + 1, col - 1, option) && is_on_board(row + 1, col - 1)) {
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
                if (is_on_board(new_row, new_col)) {
                    if (is_empty(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(new_row, new_col, option)) {
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
                if (is_on_board(row - i, col)) {
                    if (is_empty(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col, option)) {
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
                if (is_on_board(row + i, col)) {
                    if (is_empty(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col, option)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row, col - i)) {
                    if (is_empty(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col - i, option)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row, col + i)) {
                    if (is_empty(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col + i, option)) {
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
                if (is_on_board(row - i, col - i)) {
                    if (is_empty(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col - i, option)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row - i, col + i)) {
                    if (is_empty(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col + i, option)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row + i, col - i)) {
                    if (is_empty(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col - i, option)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row + i, col + i)) {
                    if (is_empty(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col + i, option)) {
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
                if (is_on_board(row - i, col)) {
                    if (is_empty(row - i, col)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col, option)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row + i, col)) {
                    if (is_empty(row + i, col)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col, option)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row, col - i)) {
                    if (is_empty(row, col - i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col - i, option)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row, col + i)) {
                    if (is_empty(row, col + i)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row, col + i, option)) {
                        (*moves)[size].row = row;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row - i, col - i)) {
                    if (is_empty(row - i, col - i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col - i, option)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row - i, col + i)) {
                    if (is_empty(row - i, col + i)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row - i, col + i, option)) {
                        (*moves)[size].row = row - i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row + i, col - i)) {
                    if (is_empty(row + i, col - i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col - i, option)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col - i;
                        (*moves)[size].type = MOVE_ATTACK;
                        size++;
                        break;
                    } else break;
                }
            }
            for (int i = 1; i < BOARD_SIZE; i++) {
                if (is_on_board(row + i, col + i)) {
                    if (is_empty(row + i, col + i)) {
                        (*moves)[size].row = row + i;
                        (*moves)[size].col = col + i;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(row + i, col + i, option)) {
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
                if (is_on_board(new_row, new_col)) {
                    if (is_empty(new_row, new_col)) {
                        (*moves)[size].row = new_row;
                        (*moves)[size].col = new_col;
                        (*moves)[size].type = MOVE_NORMAL;
                        size++;
                    } else if (is_enemy_piece(new_row, new_col, option)) {
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

bool is_valid_move(int row, int col, int old_row, int old_col)
{
    if (!is_on_board(row, col)) return false;
    
    if (!DEBUG_MODE){
        printf("\n=== Debug Validation Mouvement ===\n");
        printf("Tentative de mouvement de (%d,%d) vers (%d,%d)\n", old_row, old_col, row, col);
        printf("Tour actuel: %s\n", turn == WHITE ? "Blanc" : "Noir");
    }
    
    // Save position
    int current_piece = board[old_row][old_col];
    int target_piece = board[row][col];
    
    // Simulate the move
    board[old_row][old_col] = EMPTY;
    board[row][col] = current_piece;
    
    // Check if the move puts or leaves the king in check for the current player
    bool in_check = is_in_check(turn);
    
    if (!DEBUG_MODE){
        printf("Après simulation, le roi %s est %s\n", 
            turn == WHITE ? "blanc" : "noir",
            in_check ? "en échec" : "sécurisé");
    }
    
    // Restore position
    board[old_row][old_col] = current_piece;
    board[row][col] = target_piece;
    
    // Un mouvement est valide s'il ne laisse pas le roi en échec
    bool is_valid = !in_check;
    if (!DEBUG_MODE){  
        printf("Mouvement %s\n", is_valid ? "valide" : "invalide");
        printf("=====================\n\n");
    }
    
    return is_valid;
}

void remove_illegal_moves(int row, int col, Move **moves, int size)
{
    if (DEBUG_MODE) {
        printf("\n=== Debug Filtrage Mouvements ===\n");
        printf("Filtrage des mouvements pour la pièce en (%d,%d)\n", row, col);
        printf("Nombre de mouvements avant filtrage: %d\n", size);
    }

    // check if is its check
    // loop on the moves that can block check
    for (int i = 0; i < size; i++)
    {
        if(!is_valid_move((*moves)[i].row, (*moves)[i].col, row, col)) {
            if (DEBUG_MODE) {
                printf("Mouvement vers (%d,%d) marqué comme illégal\n", 
                    (*moves)[i].row, (*moves)[i].col);
            }
            (*moves)[i].type = MOVE_ILLEGAL;
        }
    }

    if (DEBUG_MODE) {
        printf("Mouvements après filtrage:\n");
        for (int i = 0; i < size; i++) {
            printf("  - (%d,%d) - Type: %s\n", 
                (*moves)[i].row, 
                (*moves)[i].col,
                (*moves)[i].type == MOVE_NORMAL ? "Normal" : 
                (*moves)[i].type == MOVE_ATTACK ? "Attaque" : "Illégal");
        }
        printf("=====================\n\n");
    }
}
//------------------
// CHECKS FUNCTIONS
//------------------
bool is_empty(int row, int col)
{
    if (!is_on_board(row, col)) return false;
    return (board[row][col] == EMPTY);
}

bool is_enemy_piece(int row, int col, bool option)
{
    if (!is_on_board(row, col)) return false;
    
    int piece = board[row][col];
    if (piece == EMPTY) return false;
    
    bool selected_piece_color = get_color(row, col);
    bool current_turn = turn;

    if (option == false)
    {
        
        return selected_piece_color != current_turn;
    }
    else
    {
        return selected_piece_color == current_turn;
    }
}

bool is_on_board(int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

bool is_in_check(bool color)
{
    int king_row = -1, king_col = -1;
    int king_piece = (color == WHITE) ? W_KING : B_KING;
    
    // Trouver la position du roi
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == king_piece) {
                king_row = i;
                king_col = j;
                break;
            }
        }
        if (king_row != -1) break;
    }
    
    if (king_row == -1) {
        // Roi non trouvé, cela ne devrait pas arriver dans un jeu normal
        return false;
    }
    
    // Vérifier si une pièce ennemie peut attaquer le roi
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != EMPTY && get_color(i, j) != color) {
                Move *moves = NULL;
                int size = get_moves(i, j, &moves, true);
                
                for (int k = 0; k < size; k++) {
                    if (moves[k].row == king_row && moves[k].col == king_col) {
                        free(moves);
                        fprintf(stdout,"in check");
                        return true;
                    }
                }
                
                if (moves != NULL) {
                    free(moves);
                }
            }
        }
    }
    return false;
}

bool can_block_check(bool color)
{
    // Check all pieces of the color
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != EMPTY && get_color(i, j) == color)
            {
                Move *moves = NULL;
                int size = get_moves(i, j, &moves, false);
                
                // Vérifier chaque mouvement possible
                for (int k = 0; k < size; k++) {
                    if (moves[k].type != MOVE_ILLEGAL) {
                        // Simuler le mouvement
                        int current_piece = board[i][j];
                        int target_piece = board[moves[k].row][moves[k].col];
                        
                        board[i][j] = EMPTY;
                        board[moves[k].row][moves[k].col] = current_piece;
                        
                        // Vérifier si le roi est toujours en échec
                        bool still_in_check = is_in_check(color);
                        
                        // Restaurer la position
                        board[i][j] = current_piece;
                        board[moves[k].row][moves[k].col] = target_piece;
                        
                        if (!still_in_check) {
                            free(moves);
                            return true; // Une pièce peut bloquer l'échec
                        }
                    }
                }
                if (moves != NULL) {
                    free(moves);
                }
            }
        }
    }
    return false;
}

bool is_checkmate(bool color)
{
    if (DEBUG_MODE) {
        printf("\n=== Debug Échec et Mat ===\n");
        printf("Vérification échec et mat pour les %s\n", color == WHITE ? "Blancs" : "Noirs");
    }

    // Vérifier d'abord si le roi est en échec
    if (!is_in_check(color)) {
        if (DEBUG_MODE) {
            printf("Le roi n'est pas en échec\n");
            printf("=====================\n\n");
        }
        return false;
    }
    if (DEBUG_MODE) {
        printf("Le roi est en échec\n");
    }
    
    // Trouver la position du roi
    int king_piece = (color == WHITE) ? W_KING : B_KING;
    int king_row = -1, king_col = -1;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == king_piece) {
                king_row = i;
                king_col = j;
                break;
            }
        }
        if (king_row != -1) break;
    }
    
    if (king_row == -1) {
        if (DEBUG_MODE) {
            printf("Roi non trouvé !\n");
            printf("=====================\n\n");
        }
        return false;
    }
    if (DEBUG_MODE) {
        printf("Position du roi: (%d,%d)\n", king_row, king_col);
    }
    
    // Vérifier si le roi peut se déplacer vers une case sûre
    Move *king_moves = NULL;
    int size = get_moves(king_row, king_col, &king_moves, false);
    if (DEBUG_MODE) {
        printf("Nombre de mouvements possibles pour le roi: %d\n", size);
    }
    
    for (int i = 0; i < size; i++) {
        if (king_moves[i].type != MOVE_ILLEGAL) {
            if (DEBUG_MODE) {
                printf("Test du mouvement du roi vers (%d,%d)\n", 
                    king_moves[i].row, king_moves[i].col);
            }
            // Simuler le mouvement du roi
            int current_piece = board[king_row][king_col];
            int target_piece = board[king_moves[i].row][king_moves[i].col];
            
            board[king_row][king_col] = EMPTY;
            board[king_moves[i].row][king_moves[i].col] = current_piece;
            
            // Vérifier si le roi est toujours en échec
            bool still_in_check = is_in_check(color);
            
            // Restaurer la position
            board[king_row][king_col] = current_piece;
            board[king_moves[i].row][king_moves[i].col] = target_piece;
            
            if (!still_in_check) {
                if (DEBUG_MODE) {
                    printf("Le roi peut s'échapper vers (%d,%d)\n", 
                        king_moves[i].row, king_moves[i].col);
                    printf("=====================\n\n");
                }
                free(king_moves);
                return false;
            }
        }
    }
    if (king_moves != NULL) {
        free(king_moves);
    }
    
    // Si le roi ne peut pas se déplacer, vérifier si une pièce peut bloquer l'échec
    bool can_block = can_block_check(color);
    if (DEBUG_MODE) {
        printf("Une pièce peut bloquer l'échec: %s\n", can_block ? "Oui" : "Non");
        printf("=====================\n\n");
    }
    
    return !can_block;
}

//-----------------
// UTILS FUNCTIONS
//-----------------
bool get_color(int row, int col)
{
    int piece = board[row][col];
    if (piece >= W_PAWN && piece <= W_KING)
        return WHITE;
    else if (piece >= B_PAWN && piece <= B_KING) 
        return BLACK;
    return WHITE;
}