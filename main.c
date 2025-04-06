#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "board.h"
#include "graphics.h"
#include "game_logic.h"
#include "utils.h"

int main(void)
{
    init_sdl();

    SDL_Window *window = create_window();
    SDL_Renderer *renderer = create_renderer(window);
    
    initialize_board();
    
    ChessPieces pieces = load_chess_pieces(renderer);

    // Affichage initial
    draw_background(renderer);
    draw_board(renderer);
    draw_pieces(renderer, pieces);
    SDL_RenderPresent(renderer);
    
    // Boucle principale
    game_loop(renderer, pieces);

    // Nettoyage
    cleanup(window, renderer, pieces);

    return 0;
}