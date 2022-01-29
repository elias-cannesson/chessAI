#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
#include "defs.h"
#include "protoypes.h"

/* this  segment of code, along with where I use the jmp_buf
 * to implement an iterative deepening framework to
 * allocate a set amount of time for the engine to
 * search is inspired by Tom Kerrigan's Simple Chess
 * Engine, 1997, tscp181.c source code */

#include <setjmp.h>
jmp_buf env;
int stopSearch;


void ComputerPlay() {
    int i, play;
    i = 0;
    ply = 0;
    searchFrames = 0;

    stopSearch = FALSE;
    setjmp(env);
    if (stopSearch) {
        while (ply > 0)
            undo();
        return;
    }

    start_time = timeElapsed();

    stop_time = start_time + max_time;

    memset(triangularArray, 0, sizeof(triangularArray));
    memset(searchHistory, 0, sizeof(searchHistory));
    for (i = 0; i <= MAXDEPTH; i++) {
        PV = TRUE;
        //play = alphaBetaMax(i, -10000, 10000);
        play = pvSearch(i, -100000, 100000);
        printf("Nodes searched: %d\tEvaluation: %d\n", searchFrames, play);
        if (play > 9000 || play < -9000)
            break;
    }

}

int pvSearch(int depth, int alpha, int beta) {
    int score, ch, foundMove;
    if (depth == 0) {
        return Quiescence(alpha, beta);
    }
    int bSearchPv = TRUE;

    searchFrames++;
    if (!(searchFrames & 1023)) {
        if (timeElapsed() >= stop_time) {
            stopSearch = TRUE;
            longjmp(env, 0);
        }
    }
    triangularLength[ply] = ply;
    //    printf("No repetition\n");
    if (fiftymoves >= 100) {
        return 0;
    }

    if (ply >= MAX_PLY - 1) {
        return Evaluation();
    }
    if (hply >= HIST_STACK - 1) {
        return Evaluation();
    }

    ch = Check(side_to_move);

    if (ch) {
        ++depth;
    }

    moveSearch = 0;
    generateMoves();
    foundMove = FALSE;
    for (int i = movesInSearch[ply]; i < movesInSearch[ply+1]; i++) {
        if (!makeMove(i)) {
            continue;
        }
        foundMove = TRUE;
        if (bSearchPv) {
            score = -pvSearch(depth -1, -beta, -alpha);
        } else {
            score = -pvSearch(depth - 1, -alpha-1, -alpha);
            if (score > alpha) {
                score = -pvSearch(depth-1,-beta, -alpha);
            }
        }
        undo();
        if (score >= beta) {
            searchHistory[moveStack[i].move.from][moveStack[i].move.to] += 1 << depth;
            return beta;
        }
        if (score > alpha) {
            alpha = score;
            bSearchPv = FALSE;
            triangularArray[ply][ply].index = i;
            for (int n = ply + 1; n < triangularLength[ply + 1]; ++n) {
                triangularArray[ply][n] = triangularArray[ply + 1][n];
            }
            triangularLength[ply] = triangularLength[ply + 1];
        }
    }
    if (!foundMove) {
        if (ch) {
            return -100000 + ply;
        }
        else {
            return 0;
        }
    }
    return alpha;
}


int Quiescence(int a, int b) {
    int i, evaluation;
    ++searchFrames;

    if ((searchFrames & 1023) == 0) {
        if (timeElapsed() >= stop_time) {
            stopSearch = TRUE;
            longjmp(env, 0);
        }
    }

    triangularLength[ply] = ply;


    if (ply >= MAX_PLY - 1) {
        return Evaluation();
    }
    if (hply >= HIST_STACK - 1) {
        return Evaluation();
    }
    evaluation = Evaluation();

    if (evaluation >= b) {
        return b;
    }
    if (evaluation > a) {
        a = evaluation;
    }
    moveSearch = 0;
    generateCaptures();
    if (PV) {
        sortTriangularArray();
    }
    for (i = movesInSearch[ply]; i < movesInSearch[ply+1]; ++i) {
        Sort(i);
        if (moveStack[i].move.capture != EMPTY) {
            if (!makeMove(i))
                continue;
            evaluation = -Quiescence(-b, -a);

            undo();
            if (evaluation > a) {
                if (evaluation >= b) {

                    return b;
                }
                a = evaluation;

                triangularArray[ply][ply].index = i;

                for (int j = ply + 1; j < triangularLength[ply + 1]; ++j) {
                    triangularArray[ply][j] = triangularArray[ply + 1][j];
                }
                triangularLength[ply] = triangularLength[ply + 1];
            }
        }
    }
    return a;
}


void OrderMoves() {
    int i;
    int moveScoreGuess = 0;
    for (i = movesInSearch[ply]; i < movesInSearch[ply+1]; i++) {
        if (moveStack[i].move.capture != EMPTY) {

            moveScoreGuess = 1000 * (moveStack[i].move.capture - moveStack[i].move.pieceType);
        }

        if (checkAttack(moveStack[i].move.to, other_side)) {
            moveScoreGuess -= 1000 * moveStack[i].move.pieceType;
        }

        moveStack[i].score += moveScoreGuess;
    }
}

void Sort(int from) {
    int i, topScore, topIndex;
    move_stack Move;

    topScore = -100;
    topIndex = from;
    i = from;
    while (i < movesInSearch[ply+1]) {
        if (moveStack[i].score > topScore) {
            topScore = moveStack[i].score;
            topIndex = i;
        }
        i++;
    }

    Move = moveStack[from];
    moveStack[from] = moveStack[topIndex];
    moveStack[topIndex] = Move;
}


void sortTriangularArray() {
    int i;
    PV = FALSE;
    for(i = movesInSearch[ply]; i < movesInSearch[ply+1]; ++i) {
        if (i == triangularArray[0][ply].index) {
            moveStack[i].score += 10000000;
            PV = TRUE;
            return;
        }
    }
}
