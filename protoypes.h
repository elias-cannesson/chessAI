
/* this file contains prototypes which will be passed to all other
 * source files */
#include <stdbool.h>

/*body_chess.c */
int timeElapsed();
int get_ms();
int runGame();
int results();

/* board.c */
void printBoard();
void initializeBoard();
void printBoard2();

/* move.c */
int parseMove(char * s);
void moveStr(int from, int to);


void generateMoves();
void knightMove(int from, int to, int offset);
void bishopMove(int from, int to, int offset);
void rookMove(int from, int to, int offset);
void queenMove(int from, int to, int offset);
void kingMove(int from, int to);
int makeMove(int index);
int Check(int side);
int checkAttack(int i, int side);
void undo();
void RandomComputerMove();

/*niceBoard.c*/
int printBoard3();

/*eval.c*/
int Evaluation();
int CountMaterial(int SIDE);
int CountPawns();
int whiteBishopPositions();
int blackBishopPositions();
int blackKnightPositions();
int whiteKnightPositions();
int blackKingOpeningPositions();
int whiteKingOpeningPositions();
int blackPawnsOpeningPos(int i);
int whitePawnsOpeningPos(int i);
int blackPawnsEGPos(int i);
int whitePawnsEGPos(int i);


/*search.c*/
void ComputerPlay();
int pvSearch(int depth, int alpha, int beta);
int negaScout(int depth, int alpha, int beta);
int principalVariation(int depth, int alpha, int beta);
int alphaBetaMax(int depth, int a, int b);
int alphaBetaMin(int depth, int a, int b);
int MINIMax(int depth, int a, int b, int maximizingPlayer);
int miniMax(int depth, int alpha, int beta);
int Quiescence(int alpha, int beta);
void OrderMoves();
void checkUp();

/*gen2.c (for captures) */
void generateCaptures();
void knightCapture(int from, int to, int offset);
void bishopCapture(int from, int to, int offset);
void rookCapture(int from, int to, int offset);
void queenCapture(int from, int to, int offset);
void kingCapture(int from, int to);
void pawnPush(int from, int to, int promotion);
void promote(int from, int to);


void Sort(int from);
void sortTriangularArray();