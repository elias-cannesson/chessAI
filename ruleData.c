#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "globals.h"

int move;
int ComputerSide;
int side_to_move;
int other_side;

int enPassant;
int castle;
int ply;
int hply;
int searchFrames;
int fiftymoves;
int promoted;
int repetition;
int check;