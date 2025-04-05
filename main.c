#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// Board
#define BOARD_SIZE 8
#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600
#define SQUARE_SIZE (BOARD_WIDTH / BOARD_SIZE)
// Position
#define BOARD_X ((WINDOW_WIDTH - BOARD_WIDTH) / 2)
#define BOARD_Y ((WINDOW_HEIGHT - BOARD_HEIGHT) / 2)

// BG
#define BG_COLOR_R 200
#define BG_COLOR_G 200
#define BG_COLOR_B 200

// Pieces
#define EMPTY 0
#define W_PAWN 1
#define W_KNIGHT 2
#define W_BISHOP 3
#define W_ROOK 4
#define W_QUEEN 5
#define W_KING 6
#define B_PAWN 7
#define B_KNIGHT 8
#define B_BISHOP 9
#define B_ROOK 10
#define B_QUEEN 11
#define B_KING 12
// Images
typedef struct {
    SDL_Texture *textures[13];
} ChessPieces;

int init_sdl();
SDL_Window *create_window();
SDL_Renderer *create_renderer(SDL_Window *window);
void get_event_loop();
void draw_background(SDL_Renderer *renderer);
void draw_board(SDL_Renderer *renderer);
void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]);
ChessPieces load_chess_pieces(SDL_Renderer *renderer);
void draw_pieces(SDL_Renderer *renderer, int board[BOARD_SIZE][BOARD_SIZE], ChessPieces pieces);
void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces);

int main(int argc, char *argv[]) {
    init_sdl();

    SDL_Window *window = create_window();
    SDL_Renderer *renderer = create_renderer(window);
    
    int board[BOARD_SIZE][BOARD_SIZE];
    initialize_board(board);
    
    ChessPieces pieces = load_chess_pieces(renderer);

    // Affichage
    draw_background(renderer);
    draw_board(renderer);
    draw_pieces(renderer, board, pieces);
    SDL_RenderPresent(renderer);

    // Main loop
    get_event_loop();

    // Destroy & quit
    cleanup(window, renderer, pieces);

    return 0;
}

int init_sdl()
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

SDL_Window *create_window()
{
    SDL_Window *window = SDL_CreateWindow("Jeu d'échecs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Error create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return renderer;
}

void get_event_loop()
{
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_Delay(16); // opti CPU
    }
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
                SDL_SetRenderDrawColor(renderer, 235, 236, 208, 255); // Couleur claire
            } else {
                SDL_SetRenderDrawColor(renderer, 115, 149, 82, 255); // Vert clair
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void initialize_board(int board[BOARD_SIZE][BOARD_SIZE])
{
    board[0][0] = B_ROOK;
    board[0][1] = B_KNIGHT;
    board[0][2] = B_BISHOP;
    board[0][3] = B_QUEEN;
    board[0][4] = B_KING;
    board[0][5] = B_BISHOP;
    board[0][6] = B_KNIGHT;
    board[0][7] = B_ROOK;
    
    // Pawn
    for (int col = 0; col < BOARD_SIZE; col++)
        board[1][col] = B_PAWN;
    
    // Empty
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < BOARD_SIZE; col++)
            board[row][col] = EMPTY;
    }
    
    // Pawn
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

ChessPieces load_chess_pieces(SDL_Renderer *renderer)
{
    ChessPieces pieces;
    
    for (int i = 0; i < 13; i++)
        pieces.textures[i] = NULL;
    
    const char *pieceFiles[13] = {
        NULL,                 // EMPTY
        "images/pieces/alpha/wp.png",  // W_PAWN
        "images/pieces/alpha/wn.png", // W_KNIGHT
        "images/pieces/alpha/wb.png", // W_BISHOP
        "images/pieces/alpha/wr.png",  // W_ROOK
        "images/pieces/alpha/wq.png", // W_QUEEN
        "images/pieces/alpha/wk.png",  // W_KING
        "images/pieces/alpha/bp.png",  // B_PAWN
        "images/pieces/alpha/bn.png", // B_KNIGHT
        "images/pieces/alpha/bb.png", // B_BISHOP
        "images/pieces/alpha/br.png",  // B_ROOK
        "images/pieces/alpha/bq.png", // B_QUEEN
        "images/pieces/alpha/bk.png"   // B_KING
    };
    
    // Load
    for (int i = 1; i < 13; i++) {
        SDL_Surface *surface = IMG_Load(pieceFiles[i]);
        if (surface == NULL) {
            fprintf(stderr, "Impossible de charger l'image %s! SDL_image Error: %s\n", pieceFiles[i], IMG_GetError());
            continue;
        }
        
        pieces.textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        if (pieces.textures[i] == NULL) {
            fprintf(stderr, "Impossible de créer la texture! SDL Error: %s\n", SDL_GetError());
        }
        
        SDL_FreeSurface(surface);
    }
    
    return pieces;
}

void draw_pieces(SDL_Renderer *renderer, int board[BOARD_SIZE][BOARD_SIZE], ChessPieces pieces)
{
    SDL_Rect destRect;
    // size
    destRect.w = SQUARE_SIZE;
    destRect.h = SQUARE_SIZE;
    
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            int piece = board[row][col];
            
            if (piece != EMPTY && pieces.textures[piece] != NULL)
            {
                //position
                destRect.x = BOARD_X + col * SQUARE_SIZE;
                destRect.y = BOARD_Y + row * SQUARE_SIZE;
                
                SDL_RenderCopy(renderer, pieces.textures[piece], NULL, &destRect);
            }
        }
    }
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer, ChessPieces pieces)
{
    // free texture from pieces
    for (int i = 1; i < 13; i++) {
        if (pieces.textures[i] != NULL)
            SDL_DestroyTexture(pieces.textures[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}