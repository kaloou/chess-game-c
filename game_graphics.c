#include "game_graphics.h"
#include "game_logic.h"

int init_sdl(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error Init SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fprintf(stderr, "Error SDL_image: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    return 0;
}

SDL_Window *create_window(void)
{
    SDL_Window *window = SDL_CreateWindow("Jeu d'échecs", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Error create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return renderer;
}

void draw_background(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 0xFF);
    SDL_RenderClear(renderer);
}

void draw_board(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            rect.x = BOARD_X + col * SQUARE_SIZE;
            rect.y = BOARD_Y + row * SQUARE_SIZE;

            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 235, 236, 208, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 115, 149, 82, 255);
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

ChessPieces load_chess_pieces(SDL_Renderer *renderer)
{
    ChessPieces pieces;
    
    for (int i = 0; i < 13; i++)
        pieces.textures[i] = NULL;
    
    const char *pieceFiles[13] = {
        NULL,
        "images/pieces/alpha/wp.png",
        "images/pieces/alpha/wn.png",
        "images/pieces/alpha/wb.png",
        "images/pieces/alpha/wr.png",
        "images/pieces/alpha/wq.png",
        "images/pieces/alpha/wk.png",
        "images/pieces/alpha/bp.png",
        "images/pieces/alpha/bn.png",
        "images/pieces/alpha/bb.png",
        "images/pieces/alpha/br.png",
        "images/pieces/alpha/bq.png",
        "images/pieces/alpha/bk.png"
    };
    
    for (int i = 1; i < 13; i++) {
        SDL_Surface *surface = IMG_Load(pieceFiles[i]);
        if (surface == NULL) {
            fprintf(stderr, "Impossible de charger l'image %s! SDL_image Error: %s\n", 
                    pieceFiles[i], IMG_GetError());
            continue;
        }
        
        pieces.textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        if (pieces.textures[i] == NULL) {
            fprintf(stderr, "Impossible de créer la texture! SDL Error: %s\n", 
                    SDL_GetError());
        }
        
        SDL_FreeSurface(surface);
    }
    
    return pieces;
}

void draw_pieces(SDL_Renderer *renderer, ChessPieces pieces)
{
    SDL_Rect destRect;
    destRect.w = SQUARE_SIZE;
    destRect.h = SQUARE_SIZE;
    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int piece = board[row][col];
            if (piece != EMPTY && pieces.textures[piece] != NULL) {
                destRect.x = BOARD_X + col * SQUARE_SIZE;
                destRect.y = BOARD_Y + row * SQUARE_SIZE;
                SDL_RenderCopy(renderer, pieces.textures[piece], NULL, &destRect);
            }
        }
    }
}

void show_moves(SDL_Renderer *renderer, int **tab_moves, int size)
{
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 180);

    for (int i = 0; i < size; i++) {
        int row = tab_moves[i][0];
        int col = tab_moves[i][1];

        rect.x = BOARD_X + col * SQUARE_SIZE;
        rect.y = BOARD_Y + row * SQUARE_SIZE;

        int centerX = rect.x + SQUARE_SIZE / 2;
        int centerY = rect.y + SQUARE_SIZE / 2;
        int radius = SQUARE_SIZE / 4;

        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (dx*dx + dy*dy <= radius*radius) {
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                }
            }
        }
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
