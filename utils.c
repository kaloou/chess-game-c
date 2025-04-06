#include "utils.h"
#include "game_graphics.h"
#include "game_logic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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