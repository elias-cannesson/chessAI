
#include "defs.h"
#include "globals.h"
#include "protoypes.h"

void generateCaptures() {
//    printf("Side to move: %d\n", side_to_move);
    int i, j, n;
    movesInSearch[ply+1] = movesInSearch[ply];
    for (i = 0; i < 64; i++) {
        if (color[i] == side_to_move) {
//            printf("pieces[%d]: %d\n", i, pieces[i]);
            if (pieces[i] == PAWN) {
//                printf("pawn!\n");
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
                }
            }
            else {
                switch(pieces[i]) {
                    case KNIGHT :

                        for (j = 0; j < 8; j++) {
                            knightCapture(i, board[mailbox[i] + piece_offsets[2][j]],
                                    j);
                        }
                        break;
                    case BISHOP :

                        for (j = 0; j < 4; j++) {
                            bishopCapture(i, board[mailbox[i] + piece_offsets[3][j]],
                                       j);
                        }
                        break;
                    case ROOK :

                        for (j = 0; j < 4; j++) {
                            rookCapture(i, board[mailbox[i] + piece_offsets[4][j]],
                                     j);
                        }
                        break;
                    case QUEEN :

                        for (j = 0; j < 8; j++) {
                            queenCapture(i, board[mailbox[i] + piece_offsets[5][j]],
                                      j);
                        }
                        break;
                    case KING :

                        for (j = 0; j < 8; j++) {
                            kingCapture(i, board[mailbox[i] + piece_offsets[1][j]]);
                        }
                        break;
                    default :
                        break;
                }
            }
        }
    }
}

void knightCapture(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
//    printf("from: %d\n", from);
//    printf("offset: %d\n", offset);
//    printf("piece_offsets[2][%d]: %d\n\n", offset, piece_offsets[2][offset]);
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[2][offset]];
//        printf("n: %d\n", n);
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.pieceType = KNIGHT;
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
        return;
    }

}

void bishopCapture(int from, int to, int offset) {
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
                MOVE_S->move.pieceType = BISHOP;
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
        return;
    }
}

void rookCapture(int from, int to, int offset) {

    move_stack * MOVE_S = NULL;
    int n;

    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[4][offset]];
//        printf("n: %d\n", n);
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.pieceType = ROOK;
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
        return;
    }

}

void queenCapture(int from, int to, int offset) {
    move_stack * MOVE_S = NULL;
    int n;
//    printf("from: %d\n", from);
//    printf("offset: %d\n", offset);
//    printf("piece_offsets[5][%d]: %d\n\n", offset, piece_offsets[5][offset]);
    for (n = from;;) {
        n = board[mailbox[n] + piece_offsets[5][offset]];
//        printf("n: %d\n", n);
        if (n == -1) {
            return;
        }
        if (color[n] != EMPTY) {
            if (color[n] == other_side) {
                MOVE_S = &moveStack[movesInSearch[ply + 1]++];
                MOVE_S->move.from = from;
                MOVE_S->move.to = n;
                MOVE_S->move.pieceType = QUEEN;
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
        return;
    }


}

void kingCapture(int from, int to) {
    move_stack *MOVE_S = NULL;
    if (to == -1)
        return;
    if (color[to] != EMPTY) {
        if (color[to] == other_side) {
            MOVE_S = &moveStack[movesInSearch[ply + 1]++];
            MOVE_S->move.from = from;
            MOVE_S->move.to = to;
            MOVE_S->move.index = moveSearch;
            MOVE_S->move.capture = pieces[to];
            MOVE_S->move.pieceType = pieces[from];
            MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
            moveSearch++;
            return;
        }
    }
    return;

}

void pawnPush(int from, int to, int promotion)
{
    move_stack *MOVE_S;

    if (promotion & 16) {
        if (side_to_move == WHITE) {
            if (to <= 7) {
                promote(from, to);
                return;
            }
        } else {
            if (to >= 56) {
                promote(from, to);
                return;
            }
        }
    }
    if (promotion == 21) {
        MOVE_S = &moveStack[movesInSearch[ply+1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = enPassant;
        MOVE_S->move.pieceType = PAWN;
        MOVE_S->move.capture = PAWN;
        MOVE_S->move.index = moveSearch;
        MOVE_S->score = 1000000;
        moveSearch++;
        return;
    }
    MOVE_S = &moveStack[movesInSearch[ply + 1]++];
    MOVE_S->move.from = from;
    MOVE_S->move.to = to;
    MOVE_S->move.index = moveSearch;
    MOVE_S->move.capture = pieces[to];
    MOVE_S->move.pieceType = pieces[from];
    if (color[to] != EMPTY) {
        MOVE_S->score = 1000000 + (pieces[to] * 10) - pieces[from];
    } else {
        MOVE_S->score = searchHistory[from][to];
    }
    moveSearch++;
}

void promote(int from, int to) {
    int i;
    move_stack *MOVE_S;

    for (i = KNIGHT; i <= QUEEN; ++i) {
        MOVE_S = &moveStack[movesInSearch[ply + 1]++];
        MOVE_S->move.from = from;
        MOVE_S->move.to = to;
        MOVE_S->move.index = moveSearch;
        MOVE_S->move.pieceType = i;
        MOVE_S->move.capture = pieces[to];
        MOVE_S->score = 1000000 + (i * 10);
        moveSearch++;
    }
}

