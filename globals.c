#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "globals.h"


//A chess program needs an internal board representation
//to maintain chess positions for its search, evaluation and game-play.

//what is the internal board representation?
// -first, we have a 10x12 board which we will use to see if a
// piece has moved off the board.
// -second, we need to know if a square is empty or not
// -third, we need to know what kind of piece resides on the square
//

int color[64];
int pieces[64];

int mailbox[64] = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
};


/* I use a 12x10 board representation so that when
 * the chess program generates moves, it knows when
 * it has run off the board */
int board[120] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
        -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
        -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
        -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
        -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
        -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
        -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
        -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

int initial_color[64] = {
         0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
         1,  1,  1,  1,  1,  1,  1,  1,
         1,  1,  1,  1,  1,  1,  1,  1
};

int initial_pieces[64] = {
         5,  3,  4,  6,  2,  4,  3,  5,
         1,  1,  1,  1,  1,  1,  1,  1,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
         1,  1,  1,  1,  1,  1,  1,  1,
         5,  3,  4,  6,  2,  4,  3,  5,
};


char square[64][2] = {
        {"a1"}, {"b1"}, {"c1"}, {"d1"}, {"e1"}, {"f1"}, {"g1"}, {"h1"},
          {"a2"}, {"b2"}, {"c2"}, {"d2"}, {"e2"}, {"f2"}, {"g2"}, {"h2"},
          {"a3"}, {"b3"}, {"c3"}, {"d3"}, {"e3"}, {"f3"}, {"g3"}, {"h3"},
          {"a4"}, {"b4"}, {"c4"}, {"d4"}, {"e4"}, {"f4"}, {"g4"}, {"h4"},
          {"a5"}, {"b5"}, {"c5"}, {"d5"}, {"e5"}, {"f5"}, {"g5"}, {"h5"},
          {"a6"}, {"b6"}, {"c6"}, {"d6"}, {"e6"}, {"f6"}, {"g6"}, {"h6"},
          {"a7"}, {"b7"}, {"c7"}, {"d7"}, {"e7"}, {"f7"}, {"g7"}, {"h7"},
          {"a8"}, {"b8"}, {"c8"}, {"d8"}, {"e8"}, {"f8"}, {"g8"}, {"h8"}
};

int go;
int moveMade;
int MOVE;

int maxTime;
int startTime;
int stop;

// we need a stack, or list, which keeps track of all the moves we made so we can undo
// the move when searching for moves
extern history historyStack[MAX_MOVES];
int moveSearch;
int movesInSearch[32];

SDL_Window *window;
SDL_Renderer *render;
SDL_Surface * imagePieces[12];
SDL_Texture * image_textures[12];
