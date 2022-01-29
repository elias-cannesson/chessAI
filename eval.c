#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "globals.h"
#include "defs.h"
#include "protoypes.h"
int Minors = 0;
int whiteQueenBool = 0;

int blackQueenBool = 0;
int RookCount = 0;
int pawnCount = 0;
int endGame = 0;

int KnightSquareBonus[64] =
        {
                -22,  -30,  -17,  -17,  -17,  -17,  -30, -22,
                  -17,  -16,  -16,   33,  33,  -16,  -16, -17,
                  -17,  20,   35,  40,  40,   35,  20, -17,
                  -17,  30,   40,  50,  50,   40,  30, -17,
                  -17,  30,   40,  50,  50,   40,  30, -17,
                  -17,  20,   35,  40,  40,   35,  20, -17,
                  -17,  -16,  -16,   23,  23,   -16,  -16, -17,
                -22,  -30,  -17,  -17,  -17,  -17,   -30, -22,
        };

int BishopSquaresOpening[64] =
        {
                -22,  -17,  -25,  -17,  -17,  -25,  -17, -22,
                  -17,  40,  -16,  15,   15,  -16,  40, -17,
                  -17,  18,  40,   22,   22,   40,   16, -17,
                  -17,  13,  25,   35,   35,   25,   13, -17,
                  -17,  13,  25,   35,   35,   25,   13, -17,
                  10,   18,  40,   22,   22,   40,   18,  10,
                  -17,  40, -16,  15,    15,  -16,   30, -17,
                -12,  -17,  -25,  -17,  -17,  -25,  -17, -12,
        };


int blackKingBonusOpening[64] =
        {
        20,  30,  0,   -5,  -5,   0,   30,  20,
         7,   5,  2,  -10, -10,   2,    5,   7,
       -12, -12, -12, -12, -12, -12,  -12, -12,
       -12, -12, -12, -12, -12, -12,  -12, -12,
       -12, -12, -12, -12, -12, -12,  -12, -12,
       -12, -12, -12, -12, -12, -12,  -12, -12,
       -12, -12, -12, -12, -12, -12,  -12, -12,
       -12, -12, -12, -12, -12, -12,  -12, -12
        };

int whiteKingBonusOpening[64] = {
        -12, -12, -12, -12, -12, -12,  -12, -12,
        -12, -12, -12, -12, -12, -12,  -12, -12,
        -12, -12, -12, -12, -12, -12,  -12, -12,
        -12, -12, -12, -12, -12, -12,  -12, -12,
        -12, -12, -12, -12, -12, -12,  -12, -12,
        -12, -12, -12, -12, -12, -12,  -12, -12,
         17,  15,  12, -10, -10,  12,   15,  17,
         30,  50,  15,  -2,  -2,  15,   50,  30,
        };

int blackKingBonusEndgame[64] = {
         0, 10, 10, 10, 10, 10, 10, 0,
         0, 15, 20, 20, 20, 20, 15, 0,
         0, 20, 25, 30, 30, 35, 20, 0,
         0, 25, 30, 40, 40, 30, 25, 0,
         0, 25, 35, 40, 40, 35, 25, 0,
        10, 25, 35, 45, 45, 35, 25, 10,
        10, 30, 40, 45, 45, 40, 30, 10,
        10, 30, 40, 45, 45, 40, 30, 10
};

int whiteKingBonusEndgame[64] = {
        10, 30, 40, 45, 45, 40, 30, 10,
        10, 30, 40, 45, 45, 40, 30, 10,
        10, 25, 35, 45, 45, 35, 25, 10,
         0, 25, 35, 40, 40, 35, 25, 0,
         0, 25, 30, 40, 40, 30, 25, 0,
         0, 20, 25, 30, 30, 35, 20, 0,
         0, 15, 20, 20, 20, 20, 15, 0,
         0, 10, 10, 10, 10, 10, 10, 0
};

int blackPawnsOpening[56] = {
        -5, -5, -5, -5, -5, -5, -5, -5,
         5,  5,-10,  0,  0,-10,  5,  5,
        16, 13,  0, 20, 20,  0, 13, 16,
        18, 18, 18, 30, 30, 18, 18, 18,
        16, 16, 16, 20, 20, 16, 16, 16,
        16, 16, 16, 16, 16, 16, 16, 16,
        20, 20, 20, 20, 20, 20, 20, 20,
};

int whitePawnsOpening[56] = {
         20, 20, 20, 20, 20, 20, 20, 20,
         16, 16, 16, 16, 16, 16, 16, 16,
         16, 16, 16, 20, 20, 16, 16, 16,
         18, 18, 18, 30, 30, 18, 18, 18,
         16, 13,  0, 20, 20,  0, 13, 16,
          5,  5,-10,  0,  0,-10,  5,  5,
         -5, -5, -5, -5, -5, 15, 15, 10,
};

int blackPawnsEndgame[64] = {
          0,   0,   0,   0,   0,   0,   0,   0,
        -15, -15, -15, -15, -15, -15, -15, -15,
        -10, -10, -10, -10, -10, -10, -10, -10,
         10,   5,   5,   3,   3,   5,   5,  10,
         15,  10,  10,   8,   8,  10,  10,  15,
         20,  13,  13,  11,  11,  13,  13,  20,
         24,  17,  17,  15,  15,  17,  17,  24,
         50,  50,  50,  50,  50,  50,  50,  50
};

int whitePawnsEndgame[64] = {
        50,  50,  50,  50,  50,  50,  50,  50,
        24,  17,  17,  15,  15,  17,  17,  24,
        20,  13,  13,  11,  11,  13,  13,  20,
        15,  10,  10,   8,   8,  10,  10,  15,
        10,   5,   5,   3,   3,   5,   5,  10,
       -10, -10, -10, -10, -10, -10, -10, -10,
       -15, -15, -15, -15, -15, -15, -15, -15,
         0,   0,   0,   0,   0,   0,   0,   0
};


int whiteRookBonus[64] = {
        20, 20, 20, 20, 20, 20, 20, 20,
        35, 35, 35, 35, 35, 35, 35, 35,
        -6, -2,  0,  5, 5,  0, -2,  -6,
        -6, -2,  0,  5, 5,  0, -2,  -6,
        -8, -3, -1,  5, 5, -1, -3,  -8,
        -8, -3, -1,  5, 5, -1, -3,  -8,
         0,  0,  0, 30, 30,  0,  0,  0,
         0,  0,  0, 30, 30, 30,  0,  0,
};

int blackRookBonus[64] = {
          0,  0,  0, 30, 30, 30,  0,  0,
          0,  0,  0, 30, 30,  0,  0,  0,
         -6, -2,  0,  5, 5,  0, -2,  -6,
         -6, -2,  0,  5, 5,  0, -2,  -6,
         -8, -3, -1,  5, 5, -1, -3,  -8,
         -8, -3, -1,  5, 5, -1, -3,  -8,
         35, 35, 35, 35, 35, 35, 35, 35,
         20, 20, 20, 20, 20, 20, 20, 20,

};



int Evaluation() {
    int perspective, evaluation;
    Minors = 0;
    whiteQueenBool = 0;
    blackQueenBool = 0;
    RookCount = 0;

    int whiteEval = CountMaterial(WHITE);
    int whiteMat = whiteEval;
    int blackEval = CountMaterial(BLACK);
    int blackMat = blackEval;


    for (int i = 0; i < 64 ; i++) {
        if (color[i] == EMPTY) {
            continue;
        }
        if (color[i] == WHITE) {
            switch(pieces[i]) {
                case KNIGHT:
                    whiteEval += KnightSquareBonus[i];
                    break;
                case BISHOP:
                    whiteEval += BishopSquaresOpening[i];
                    if (i == 43) {
                        if (pieces[51] == PAWN) {
                            whiteEval -= 30;
                        }
                    }
                    else if (i == 44) {
                        if (pieces[52] == PAWN) {
                            whiteEval -= 30;
                        }
                    }
                    break;
                case KING:
                    if ( whiteMat < 1800 )
                        whiteEval += whiteKingBonusEndgame[i];
                    else
                        whiteEval += whiteKingBonusOpening[i];
                    break;
                case ROOK:
                    whiteEval += whiteRookBonus[i];
                    break;
                case PAWN:
                    if (whiteMat + blackMat < 3600) {
                        whiteEval += whitePawnsEGPos(i);
                    } else {
                        whiteEval += whitePawnsOpeningPos(i);
                    }
                default:
                    break;
            }
        }
        else if (color[i] == BLACK) {
            switch(pieces[i]) {
                case KNIGHT:
                    blackEval += KnightSquareBonus[i];
                    break;
                case BISHOP:
                    blackEval += BishopSquaresOpening[i];
                    if (i == 19) {
                        if (pieces[11] == PAWN) {
                            blackEval -= 30;
                        }
                    } else if (i == 20) {
                        if (pieces[12] == PAWN) {
                            blackEval -= 30;
                        }
                    }
                    break;
                case KING:
                    if ( blackMat < 1800 )
                        blackEval += blackKingBonusEndgame[i];
                    else
                        blackEval += blackKingBonusOpening[i];
                    break;
                case ROOK:
                    blackEval += blackRookBonus[i];
                    break;
                case PAWN:
                    if (whiteMat + blackMat < 3600) {
                        blackEval += blackPawnsEGPos(i);
                    } else {
                        blackEval += blackPawnsOpeningPos(i);
                    }
                default:
                    break;
            }
        }
    }
    evaluation = whiteEval - blackEval;
    if (side_to_move == WHITE) {
        perspective = 1;
    } else {
        perspective = -1;
    }

    return evaluation * perspective;

}

int blackPawnsOpeningPos(int i) {
    int score = 0;

    score += blackPawnsOpening[i];
    if (i >= 16) {
        if (pieces[i-8] == PAWN && color[i-8] == BLACK) {
            score -= 15;
        }
    }
    return score;
}

int whitePawnsOpeningPos(int i) {
    int score = 0;
    score += whitePawnsOpening[i];
    if (i <= 47) {
        if (pieces[i+8] == PAWN && color[i+8] == BLACK) {
            score -= 15;
        }
    }
    return score;
}

int blackPawnsEGPos(int i) {
    int score = 0;
    score += blackPawnsEndgame[i];
    return score;
}

int whitePawnsEGPos(int i) {
    int score = 0;
    score += whitePawnsEndgame[i];
    return score;
}

int whiteBishopPositions() {
    for (int i = 63; i >= 0; --i) {
        if (pieces[i] == BISHOP && color[i] == WHITE) {
            return BishopSquaresOpening[i];
        }
    }
    return 0;
}

int blackBishopPositions() {
    for (int i = 0; i < 64; i++) {
        if (pieces[i] == BISHOP && color[i] == BLACK) {
            return BishopSquaresOpening[i];
        }
    }
    return 0;
}

int whiteKnightPositions() {
    for (int i = 63; i >= 0; --i) {
        if (pieces[i] == KNIGHT && color[i] == WHITE) {
            return KnightSquareBonus[i];
        }
    }
    return 0;
}

int blackKnightPositions() {
    for (int i = 0; i < 64; i++) {
        if (pieces[i] == KNIGHT && color[i] == BLACK) {
            return KnightSquareBonus[i];
        }
    }
    return 0;
}

int whiteKingOpeningPositions() {
    for (int i = 63; i >= 0; --i) {
        if (pieces[i] == KING && color[i] == WHITE) {
            return whiteKingBonusOpening[i];
        }
    }
    return 0;
}

int blackKingOpeningPositions() {
    for (int i = 0; i < 64; i++) {
        if (pieces[i] == KING && color[i] == BLACK) {
            return blackKingBonusOpening[i];
        }
    }
    return 0;
}



int CountPawns() {
    int pawns = 0;
    for (int i = 0; i < 64; i++) {
        if (pieces[i] == PAWN) {
            pawns++;
        }
    }
    return pawns;
}


int CountMaterial(int SIDE) {
    int material = 0;
    //keep track of pawnCount to
    pawnCount = CountPawns();
    for (int i = 0; i < 64; i++) {
        if (color[i] == SIDE) {
                switch(pieces[i]) {
                    case PAWN:
                        material += 100;
                        break;
                    case KNIGHT:
                        Minors++;
                        if (pawnCount > 13)
                            material += 300;
                        else if (pawnCount < 13 && pawnCount > 8)
                            material += 280;
                        else
                            material += 270;
                        break;
                    case BISHOP:
                        Minors++;
                        if (pawnCount > 13)
                            material += 288;
                        else if (pawnCount < 13 && pawnCount > 8)
                            material += 300;
                        else
                            material += 320;
                        break;
                    case ROOK:
                        RookCount++;
                        material += 500;
                        break;
                    case QUEEN:
                        if (SIDE == WHITE)
                            whiteQueenBool = TRUE;
                        else
                            blackQueenBool = TRUE;
                        material += 950;
                        break;
                    case KING:
                        material += 40000;
                        break;
                    default:
                        break;
                }
            }
        }
    return material;
    }