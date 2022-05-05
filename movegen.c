#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defs.h"
#include "globals.h"
#include "protoypes.h"
#include <ctype.h>


// This function loops over each square in the board and checks if there is a piece on that square
// that matches the current side's color. if it does, pseudo-legal moves are pushed onto the current
// position's stack of moves
void generateMoves() {
    auto int i, j;

    movesInSearch[ply+1] = movesInSearch[ply];

    for (i = 0; i < 64; i++) {

        if (color[i] == side_to_move) {
            if (pieces[i] == PAWN) {
                if (side_to_move == WHITE) {
                    if ((i & 7) != 0 && i - 9 == enPassant) {
                        pawnPush(i, enPassant, 21);
                    }
                    if ((i & 7) != 7 && i - 7 == enPassant) {
                        pawnPush(i, enPassant, 21);
                    }
                    if ((i & 7) != 0 && color[i - 9] == BLACK)
                        pawnPush(i, i - 9, 17);
                    if ((i & 7) != 7 && color[i - 7] == BLACK)
                        pawnPush(i, i - 7, 17);
                    if (color[i - 8] == EMPTY) {
                        pawnPush(i, i - 8, 16);
                        if (i >= 48 && color[i - 16] == EMPTY)
                            pawnPush(i, i - 16, 24);
                    }
                } else {
                    if ((i & 7) != 0 && i + 7 == enPassant) {
                        pawnPush(i, enPassant, 21);
                    }
                    if ((i & 7) != 7 && i + 9 == enPassant) {
                        pawnPush(i, enPassant, 21);
                    }
                    if ((i & 7) != 0 && color[i + 7] == WHITE)
                        pawnPush(i, i + 7, 17);
                    if ((i & 7) != 7 && color[i + 9] == WHITE)
                        pawnPush(i, i + 9, 17);
                    if (color[i + 8] == EMPTY) {
                        pawnPush(i, i + 8, 16);
                        if (i <= 15 && color[i + 16] == EMPTY)
                            pawnPush(i, i + 16, 24); }

                }

            }
            else {
                switch(pieces[i]) {
                    case KNIGHT :

                        for (j = 0; j < 8; j++) {
                            knightMove(i, board[mailbox[i] + piece_offsets[2][j]],
                                       j);
                        }
                        break;
                    case BISHOP :

                        for (j = 0; j < 4; j++) {
                            bishopMove(i, board[mailbox[i] + piece_offsets[3][j]],
                                       j);
                        }
                        break;
                    case ROOK :
                        for (j = 0; j < 4; j++) {
                            rookMove(i, board[mailbox[i] + piece_offsets[4][j]],
                                     j);
                        }
                        break;
                    case QUEEN :

                        for (j = 0; j < 8; j++) {
                            queenMove(i, board[mailbox[i] + piece_offsets[5][j]],
                                      j);
                        }
                        break;
                    case KING :

                        for (j = 0; j < 8; j++) {
                            kingMove(i, board[mailbox[i] + piece_offsets[1][j]]);
                        }
                        if (side_to_move == WHITE) {

                                if (castle & WhiteKCastle) {
                                    kingMove(i, i + 2);
                                }
                                if (castle & WhiteQCastle) {
                                    kingMove(i, i - 2);
                                }

                        } else {

                                if (castle & BlackKCastle) {
                                    kingMove(i, i + 2);
                                }
                                if (castle & BlackQCastle) {
                                    kingMove(i, i - 2);
                                }

                        }
                        break;
                    default :
                        break;
                }

            }

        }
    }
}



void knightMove(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[2][offset]];
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.capture = pieces[n];
                MOVE_S->move.pieceType = pieces[from];
                MOVE_S->move.index = moveSearch;
                MOVE_S->move.promoted = FALSE;
                MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
                moveSearch++;
                return;
            } else {
                return;
            }
        }
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = n;
        MOVE_S->move.capture = pieces[n];
        MOVE_S->move.pieceType = pieces[from];
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.promoted = FALSE;

        MOVE_S->score = searchHistory[from][to];

        moveSearch++;
        break;
    }
}

void bishopMove(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[3][offset]];
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.capture = pieces[n];
                MOVE_S->move.pieceType = pieces[from];
                MOVE_S->move.index = moveSearch;
                MOVE_S->move.promoted = FALSE;
                MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
                moveSearch++;
                return;
            } else {
                return;
            }
        }
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = n;
        MOVE_S->move.capture = pieces[n];
        MOVE_S->move.pieceType = pieces[from];
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.promoted = FALSE;
        MOVE_S->score = searchHistory[from][to];

        moveSearch++;
    }

}

void rookMove(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[4][offset]];
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.capture = pieces[n];
                MOVE_S->move.pieceType = pieces[from];
                MOVE_S->move.index = moveSearch;
                MOVE_S->move.promoted = FALSE;
                MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
                moveSearch++;
                return;
            } else {
                return;
            }
        }
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = n;
        MOVE_S->move.capture = pieces[n];
        MOVE_S->move.pieceType = pieces[from];
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.promoted = FALSE;

        MOVE_S->score = searchHistory[from][to];

        moveSearch++;
    }
}

void queenMove(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[5][offset]];
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.capture = pieces[n];
                MOVE_S->move.pieceType = pieces[from];
                MOVE_S->move.index = moveSearch;
                MOVE_S->move.promoted = FALSE;
                MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
                moveSearch++;
                return;
            } else {
                return;
            }
        }
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = n;
        MOVE_S->move.capture = pieces[n];
        MOVE_S->move.pieceType = pieces[from];
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.promoted = FALSE;
        MOVE_S->score = searchHistory[from][to];

        moveSearch++;
    }
}


void kingMove(int from, int to) {
    move_stack * MOVE_S = NULL;
    if (to == -1)
        return;
    if (color[to] != EMPTY) {
        if (color[to] == other_side) {
            MOVE_S = &moveStack[movesInSearch[ply + 1]++];
            MOVE_S->move.from = from;
            MOVE_S->move.to = to;
            MOVE_S->move.index = moveSearch;
            MOVE_S->move.capture = pieces[to];
            MOVE_S->move.pieceType = KING;
            MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
            moveSearch++;
            return;
        }
    }
    else {
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = to;
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.capture = EMPTY;
        MOVE_S->move.pieceType = KING;
        MOVE_S->score = searchHistory[from][to];
        moveSearch++;
    }

}


// a very important function which makes the move specified by the user, or in the case of the computer,
// a move that is available in the current position. a move is pushed onto the history stack, or the record
// of the moves that have been played so far along with information about the enPassant square, the castle
// bitfield, the current count towards fifty moves without captures, and the hash for the position.

int makeMove(int index) {
    int from, to;
    auto int tempCastle = castle;
    int from2, to2;
    from = moveStack[index].move.from;
    to = moveStack[index].move.to;
    
    if (abs(from - to) == 2 && moveStack[index].move.pieceType == KING) {
        if (Check(side_to_move)) {
            return FALSE;
        }
        switch (to) {
            case 62 :
                if (color[61] != EMPTY || color[62] != EMPTY ||
                        checkAttack(61, other_side) || checkAttack(62, other_side)) {
                    return FALSE;
                }
                castle ^= WhiteKCastle;
                from2 = 63;
                to2 = 61;
                break;
            case 58 :
                if (color[57] != EMPTY || color[58] != EMPTY || color[59] != EMPTY
                 || checkAttack(58, other_side) || checkAttack(59, other_side)) {
                    return FALSE;
                }
                castle ^= WhiteQCastle;
                from2 = 56;
                to2 = 59;
                break;
            case 6:
                if (color[5] != EMPTY || color[6] != EMPTY ||
                        checkAttack(5, other_side) || checkAttack(6, other_side)) {
                    return FALSE;
                }
                castle ^= BlackKCastle;
                from2 = 7;
                to2 = 5;
                break;
            case 2:
                if (color[3] != EMPTY || color[2] != EMPTY || color[1] != EMPTY ||
                checkAttack(3, other_side) || checkAttack(2, other_side)) {
                    return FALSE;
                }
                castle ^= BlackQCastle;
                from2 = 0;
                to2 = 3;
            default:
                from2 = -1;
                to2 = -1;
        }
        if (color[from2] != side_to_move && pieces[from2] != ROOK) {
            return FALSE;
        } else {
            color[to2] = color[from2];
            pieces[to2] = pieces[from2];
            color[from2] = EMPTY;
            pieces[from2] = EMPTY;
        }

    }
    historyStack[hply].move = moveStack[index].move;
    historyStack[hply].enPassant = enPassant;
    historyStack[hply].castle = castle;
    historyStack[hply].fiftymoves = fiftymoves;


    if (moveStack[index].move.pieceType == PAWN && to == enPassant) {
        pieces[from] = EMPTY;
        color[from] = EMPTY;
        pieces[to] = PAWN;
        color[to] = side_to_move;
        historyStack[hply - 1].move.pieceType = EMPTY;
        pieces[historyStack[hply - 1].move.to] = EMPTY;
        color[historyStack[hply - 1].move.to] = EMPTY;
        historyStack[hply-1].move.enP = TRUE;
    } else {
        pieces[from] = EMPTY;
        color[from] = EMPTY;
        pieces[to] = moveStack[index].move.pieceType;
        color[to] = side_to_move;
        historyStack[hply-1].move.enP = FALSE;
    }

    // this bit of code detects if an enPassant square has been created.
    if (moveStack[index].move.pieceType == PAWN && abs(from - to) == 16) {
        if (side_to_move == WHITE) {
            enPassant = from - 8;
        } else {
            enPassant = from + 8;
        }
    } else {
        enPassant = -1;
    }
    hply++;
    ply++;
    side_to_move ^= 1;
    other_side ^= 1;
    
    if (Check(other_side)) {
        undo();
        return FALSE;
    } else {
        return TRUE;
    }

}



void undo() {
    auto int from, to;
    --hply;
    --ply;
    side_to_move ^= 1;
    other_side ^= 1;
    from = historyStack[hply].move.from;
    to = historyStack[hply].move.to;

    enPassant = historyStack[hply].enPassant ;
    castle = historyStack[hply-1].castle;
    fiftymoves = historyStack[hply].fiftymoves;

    if (abs(from - to) == 2 && historyStack[hply].move.pieceType == KING) {
        int from2, to2;
        switch (to) {
            case 62:
                from2 = 61;
                to2 = 63;
                break;
            case 58:
                from2 = 59;
                to2 = 56;
                break;
            case 2:
                from2 = 3;
                to2 = 0;
                break;
            case 6:
                from2 = 5;
                to2 = 7;
                break;
            default:
                from2 = -1;
                to2 = -1;
                break;
        }
        color[to2] = side_to_move;
        pieces[to2] = ROOK;
        color[from2] = EMPTY;
        pieces[from2] = EMPTY;
    }

    if (enPassant != -1 && historyStack[hply-1].move.enP == TRUE) {
        pieces[to] = EMPTY;
        color[to] = EMPTY;
        pieces[historyStack[hply-1].move.to] = PAWN;
        color[historyStack[hply-1].move.to] = other_side;
        historyStack[hply-1].move.pieceType = PAWN;
        pieces[from] = PAWN;
    } else {
        if (historyStack[hply].move.capture == EMPTY) {
            if (historyStack[hply].move.promoted == TRUE) {
                pieces[from] = PAWN;
            } else {
                pieces[from] = historyStack[hply].move.pieceType;
            }
            pieces[to] = EMPTY;
            color[to] = EMPTY;
        } else {
            if (historyStack[hply].move.promoted == TRUE) {
                pieces[from] = PAWN;
            } else {
                pieces[from] = historyStack[hply].move.pieceType;
            }
            pieces[to] = historyStack[hply].move.capture;
            color[to] = other_side;
        }
    }

    color[from] = side_to_move;
}


int Check(int side) {
    int i;
    for (i = 0; i < 64; i++) {
        if (pieces[i] == KING && color[i] == side) {
            return checkAttack(i, side ^ 1);
        }
    }
    return TRUE;
}


int checkAttack(int i, int side) {
    int j, direction, potentialSquare;
    for (j = 0; j < 64; j++) {
        if (color[j] == side) {
            if (pieces[j] == PAWN) {
                if (side == WHITE) {
                    if (board[mailbox[j] - 11] != -1) {
                        if (j - 9 == i) {
                            return TRUE;
                        }
                    }

                    if (board[mailbox[j] - 9] != -1) {
                        if (j - 7 == i) {
                            return TRUE;
                        }
                    }
                } else {

                    if (board[mailbox[j] + 11] != -1) {
                        if (j + 9 == i) {
                            return TRUE;
                        }
                    }

                    if (board[mailbox[j] + 9] != -1) {
                        if (j + 7 == i) {
                            return TRUE;
                        }
                    }
                }
            } else {
                switch (pieces[j]) {
                    case KNIGHT:
                        for (direction = 0; direction < 8; direction++) {

                            for (potentialSquare = j;;) {
                                potentialSquare = board[mailbox[j] + piece_offsets[2][direction]];
                                if (potentialSquare == -1) {
                                    break;
                                }
                                if (potentialSquare == i) {
                                    return TRUE;
                                }
                                if (color[potentialSquare] != EMPTY) {
                                    break;
                                }
                                else {
                                    break;
                                }
                            }

                        }
                        break;
                    case BISHOP :
                        for (direction = 0; direction < 4; direction++) {
                            for (potentialSquare = j;;) {
                                potentialSquare = board[mailbox[potentialSquare] + piece_offsets[3][direction]];
                                if (potentialSquare == -1) {
                                    break;
                                }
                                if (potentialSquare == i) {
                                    return TRUE;
                                }
                                if (color[potentialSquare] != EMPTY) {
                                    break;
                                }
                            }
                        }
                        break;
                    case ROOK :
                        for (direction = 0; direction < 4; direction++) {
                            for (potentialSquare = j;;) {
                                potentialSquare = board[mailbox[potentialSquare] + piece_offsets[4][direction]];
                                if (potentialSquare == -1) {
                                    break;
                                }
                                if (potentialSquare == i) {
                                    return TRUE;
                                }
                                if (color[potentialSquare] != EMPTY) {
                                    break;
                                }
                            }
                        }
                        break;
                    case QUEEN :
                        for (direction = 0; direction < 8; direction++) {
                            for (potentialSquare = j;;) {
                                potentialSquare = board[mailbox[potentialSquare] + piece_offsets[5][direction]];
                                if (potentialSquare == -1) {
                                    break;
                                }
                                if (potentialSquare == i) {
                                    return TRUE;
                                }
                                if (color[potentialSquare] != EMPTY) {
                                    break;
                                }
                            }
                        }
                        break;
                    // still need to check if a king is attackign...

                    default :
                        break;
                }
            }
        }
    }
    return FALSE;
}

void RandomComputerMove() {
    int i;
    int randomNum;
    randomNum = (rand() % (moveSearch + 1));
    printf("randomNum: %d\n", randomNum);
    for (i = 0; i < moveSearch; i++) {
        if (!makeMove(randomNum)) {
            undo();
            randomNum = (rand() % (moveSearch + 1));
            continue;
        } else {
            printf("moveStack[%d].from: %d\n", randomNum,
                   moveStack[randomNum].move.from);
            break;
        }
    }

}
