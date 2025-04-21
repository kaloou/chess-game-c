#include "utils.h"
#include "game_graphics.h"
#include "game_logic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

bool waiting_for_move = false;
int selected_row = -1, selected_col = -1;
Move *possible_moves = NULL;
int moves_size = 0;

void reset_params(void)
{
    waiting_for_move = false;
    selected_row = -1;
    selected_col = -1;
    reset_moves();
}

void reset_moves(void)
{
    if (possible_moves != NULL)
    {
        free(possible_moves);
        possible_moves = NULL;
    }
    moves_size = 0;
}


void display_moves(SDL_Renderer *renderer, ChessPieces pieces)
{
    draw_background(renderer);
    draw_board(renderer);
    draw_pieces(renderer, pieces);
    if (waiting_for_move) {
        show_moves(renderer, possible_moves, moves_size);
    }
    SDL_RenderPresent(renderer);
}

bool handle_first_click(int row, int col)
{
    // check if right color turn
    bool piece_color = get_color(row, col);
    if (piece_color != turn)
        return false;

    reset_moves();

    moves_size = get_moves(row, col, &possible_moves, false);
    remove_illegal_moves(row, col, &possible_moves, moves_size);

    // Debug messages
    if (DEBUG_MODE)
    {
        printf("\n=== Debug Mouvements ===\n");
        printf("Pièce sélectionnée: (%d,%d) - Couleur: %s\n", row, col, piece_color == WHITE ? "Blanc" : "Noir");
        printf("Tour actuel: %s\n", turn == WHITE ? "Blanc" : "Noir");
        printf("Nombre de mouvements possibles: %d\n", moves_size);
        printf("Mouvements possibles:\n");
        for (int i = 0; i < moves_size; i++)
        {
            printf("  - (%d,%d) - Type: %s\n", 
            possible_moves[i].row, 
            possible_moves[i].col,
            possible_moves[i].type == MOVE_NORMAL ? "Normal" : 
                possible_moves[i].type == MOVE_ATTACK ? "Attaque" : "Illégal");
        }
        printf("=====================\n\n");
    }

    if (moves_size == 0)
    {
        reset_moves();
        return false;
    }

    // Save params
    selected_row = row;
    selected_col = col;
    waiting_for_move = true;
    return true;
}

bool handle_second_click(int row, int col)
{
    // Vérifier si le clic est sur un mouvement valide
    for (int i = 0; i < moves_size; i++)
    {
        if (possible_moves[i].row == row && possible_moves[i].col == col && possible_moves[i].type != MOVE_ILLEGAL) {
            // move piece
            int piece = board[selected_row][selected_col];
            board[selected_row][selected_col] = EMPTY;
            board[row][col] = piece;

            if (is_checkmate(!turn))
            {
                printf("Échec et mat !\n");
                initialize_board();
                if (turn != WHITE) turn = WHITE;
                return true;
            }

            switch_turn();
            return true;
        }
    }
    return false;
}

void click(int row, int col, SDL_Renderer *renderer, ChessPieces pieces)
{   
    if (is_on_board(row,col))
    {
        if (!waiting_for_move) // first click
        {   
            if (handle_first_click(row, col))
            {
                display_moves(renderer, pieces);
            }
        }
        else // second click
        {
            if (handle_second_click(row, col))
            {
                reset_params();
                display_moves(renderer, pieces);
            }
            else
            {
                reset_params();
                display_moves(renderer, pieces);
            }
        }
    }
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
                case SDL_QUIT: // quit game
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN: // left click
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
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

void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces)
{
    for (int i = 1; i < 13; i++) {
        if (pieces.textures[i] != NULL)
            SDL_DestroyTexture(pieces.textures[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
} 

void switch_turn(void)
{
    turn = (turn == WHITE) ? BLACK : WHITE;
}