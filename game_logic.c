#include "game_logic.h"
#include "board.h"
#include "utils.h"

bool turn = WHITE;

void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces)
{   
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        int **possible_moves = malloc(27 * sizeof(int *));
        for (int i = 0; i < 27; i++) {
            possible_moves[i] = malloc(2 * sizeof(int));
        }

        int size = get_moves(row, col, possible_moves);

        draw_background(renderer);
        draw_board(renderer);
        draw_pieces(renderer, pieces);
        show_moves(renderer, possible_moves, size);
        SDL_RenderPresent(renderer);

        for (int i = 0; i < 27; i++) {
            free(possible_moves[i]);
        }
        free(possible_moves);
    }
}

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

void game_loop(SDL_Renderer *renderer, ChessPieces pieces)
{
    SDL_Event event;
    int quit = 0;
    int mouseX, mouseY;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        int clickX = (mouseX - BOARD_X) / SQUARE_SIZE;
                        int clickY = (mouseY - BOARD_Y) / SQUARE_SIZE;
                        click(clickY, clickX, renderer, pieces);
                    }
                    break;
            }
        }
        SDL_Delay(16);
    }
} 