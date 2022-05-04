#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//globals.c
extern int color[64];
extern int pieces[64];
extern int mailbox[64];
extern int board[120];
extern int initial_pieces[64];
extern int initial_color[64];

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Surface * imagePieces[12];
extern SDL_Texture * image_textures[12];

extern int moveMade;
extern int go;
extern int MOVE;

extern int maxTime;
extern int startTime;
extern int stop;

extern int moveSearch;
extern int movesInSearch[32];

extern char square[64][2];

//pieceData.c
extern int offsets[6][8];
extern int offsets2[6][8];
extern char pieceString[6];

// rulesData.c
extern int move;
extern int ComputerSide;
extern int side_to_move;
extern int other_side;

extern int castle;
extern int enPassant;
extern int ply;
extern int hply;
extern int searchFrames;
extern int fiftymoves;
extern int promoted;
extern int repetition;
extern int check;

// pvtable.c
extern int triangularLength[64];
extern int PV;
extern int searchHistory[64][64];
