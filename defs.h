#include <stdlib.h>
#include <stdio.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) {       \
printf("%s - Failed ", #n); \
printf("On %s ", __DATE__);\
printf("At %s ", __TIME__); \
printf("In File %s ", __FILE__);\
printf("At Line %s\n", __LINE__); \
exit(1); }
#endif

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


#define MAX_PLY			36
#define HIST_STACK		500
#define MAXDEPTH 11

//the type of piece we are on... these piece numbers are arbitrary
#define PAWN 1
#define KING 2
#define KNIGHT 3
#define BISHOP 4
#define ROOK 5
#define QUEEN 6
#define NO_PIECE 7


#define BLACK 0
#define WHITE 1
#define OFFBOARD -1
#define NONE -2

#define EMPTY 99


#define NOMOVE 0

// these are the rough values of pieces when evaluating
// a chess position according to common convention.
#define PAWNVALUE 100
#define KNIGHTVALUE 300
#define BISHOPVALUE 320
#define ROOKVALUE 500
#define QUEENVALUE 1000
#define KINGVALUE 50000

// our castle variable is a four-bit field. it begins with
// the value 15. when we bitwise-& these values with the castle
// bitfield, we can check if a castle is available as a pseudo-legal
// move. If we make any four of these castles, our global castle
// bitfield is XOR-ed with the corresponding value.
enum { WhiteKCastle = 1, WhiteQCastle = 2, BlackKCastle = 4, BlackQCastle = 8};


#define TRUE 1
#define FALSE 0
#define PROMOTE 1
#define MAX_MOVES 2048

// this structure is used as a move data type.
// every move keeps track of the squares from and to,
// the type of piece that made the move, if a piece
// was captured and if so its piecetype, if the move
// was an enPassant capture, the move's index in
// the list of moves generated, and if it was
// a promotion. Now, if I was a better programmer,
// i would have reduced the memory of each move struct
// by encoding information in a bitfield. That is on
// my checklist as i keep working on this project.
typedef struct {
    int from;
    int to;
    int pieceType;
    int capture;
    short enP;
    int index;
    int promoted;
} move_t;

// our moveStack is just a stack of
// the moves generated. It keeps track of the
// "score" of the move so alpha-beta search can
// prioritize making captures when the engine searches
// a position...
typedef struct {
    move_t move;
    int score;
} move_stack;

move_stack moveStack[MAX_MOVES];
move_stack captureStack[40];

// the history stack is crucial for keeping track
// of moves made when searching, as it allows the engine
// to pop a move from the history stack and return to
// an earlier position when it searches possible moves.
typedef struct {
    move_t move;
    int castle;
    int enPassant;
    int ply;
    int hply;
    int fiftymoves;
    int hash;
} history;


history historyStack[MAX_MOVES];

move_t checkingPieces[6];

move_t lastMove;

move_t triangularArray[32][32];

move_t searchKillers[2][MAXDEPTH];




