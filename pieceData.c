#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "globals.h"


char pieceString[6] = {
        'P', 'K', 'N', 'B', 'R', 'Q'
};

int offsets[6][8] = {
        /*pawn*/   {0, 0, 0, 0, 0, 0, 0, 0},
        /*king*/   {-11, -10, -9, -1, 1, 9, 10, 11 },
        /*kNight*/ {-21, -19, -8, 12, 21, 19, 8, -12},
        /*bishop*/ {-11, -9, 9, 11, 0, 0, 0, 0 },
        /*rook*/   {-10, -1, 1, 10, 0, 0, 0, 0 },
        /*queen*/  {-11, -10, -9, -1, 1, 9, 10, 11 }
};

int offsets2[6][8] = {
        /*pawn*/   {0, 0, 0, 0, 0, 0, 0, 0},
        /*king*/   {-9, -8, -7, -1, 1, 7, 8, 9},
        /*kNight*/ {-17, -15, -6, 10, 17, 15, 6, -10},
        /*bishop*/ {-9, -7, 7, 9, 0, 0, 0, 0 },
        /*rook*/   {-8, -1, 1, 8, 0, 0, 0, 0 },
        /*queen*/  {-9, -8, -7, -1, 1, 7, 8, 9 }
};

int triangularLength[64];
int PV;
int searchHistory[64][64];
