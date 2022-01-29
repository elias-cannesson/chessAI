#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "globals.h"
#include "protoypes.h"

int parseMove(char * s) {
    auto int from, to,i;
    from = (s[0] - 'a');
    from += 8 * (8 - (s[1]-'0'));
    to = (s[2] - 'a');
    to += 8 * (8 - (s[3]-'0'));
    if (strlen(s) == 5) {
        printf("str len is 5\n");
        for (i = 0; i < movesInSearch[1]; i++) {
            if (moveStack[i].move.from == from && moveStack[i].move.to == to) {
                printf("The move is on the stack\n");
                switch(s[4]) {
                    case 'N' :
                    case 'n' :
                        if (moveStack[i].move.pieceType == KNIGHT) {
                            return i;
                        }
                        break;
                    case 'B' :
                    case 'b' :
                        if (moveStack[i].move.pieceType == BISHOP) {
                            return i;
                        }
                        break;
                    case 'R' :
                    case 'r' :
                        if (moveStack[i].move.pieceType == ROOK) {
                            return i;
                        }
                        break;
                    case 'Q' :
                    case 'q' :
                        if (moveStack[i].move.pieceType == QUEEN) {
                            return i;
                        }
                        break;
                    default :
                        break;
                }
            }
        }
    } else {
        for (i = 0; i < movesInSearch[ply+1]; i++) {
            if (moveStack[i].move.from == from && moveStack[i].move.to == to) {
                return i;
            }
        }
    }

    return -1;
}

void moveStr(int from, int to) {
    int i, j;

    if (from < to) {
        for (i = 0; i < 64; i++) {
            if (i == from) {
                printf("%c%c", square[i][0], square[i][1]);
            }
            if (i == to) {
                printf("%c%c", square[i][0], square[i][1]);
            }
        }
    } else {
        for (i = 63; i >= 0; i--) {
            if (i == from) {
                printf("%c%c", square[i][0], square[i][1]);
            }
            if (i == to) {
                printf("%c%c", square[i][0], square[i][1]);
            }
        }
    }
}

//void parseFen(char * s) {
//
//    for (int i = 0; i < 64; i++) {
//
//    }
//
//}