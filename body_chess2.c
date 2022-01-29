#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "globals.h"
#include "protoypes.h"

/* iterative deepening framework borrowed from Tom Kerrigan's
 * Simple Chess Engine */
#include <sys/timeb.h>
int ftime_ok = FALSE;
int get_ms()
{
    struct timeb timebuffer;
    ftime(&timebuffer);
    if (timebuffer.millitm != 0)
        ftime_ok = TRUE;
    return (timebuffer.time * 1000) + timebuffer.millitm;
}

int runGame() {
    ComputerSide = NONE;
    init_hash();
    initializeBoard();
    generateMoves();
    max_time = 1 << 25;
    printf("max_time: %d\n", max_time);
    // this is the string input from the user
    char s[256];
    int i;
    int increment = 7;
    int Result = 0;


    // we are gonna fetch certain commands from the user.
    printf("Welcome to the Extra Credit Engine of Chess by Elias Cannesson, \n");
    printf("ECECEC. Enter 'help' for a list of commands to use the engine. \n");

    while (MOVE) {

        if (side_to_move == ComputerSide) {
            ComputerPlay();      
//                    printf("PV[0][0].from: %d, .to: %d, .pieceType: %d, .capture:%d, .index: %d\n",
//                           triangularArray[0][0].from,triangularArray[0][0].to, triangularArray[0][0].pieceType,
//                           triangularArray[0][0].capture, triangularArray[0][0].index);
//                    printf("Size of movestack: %lu\n", sizeof(moveStack)/sizeof(move_stack));
//            moveStr(triangularArray[0][0].index);
            makeMove(triangularArray[0][0].index);
            printBoard2();
            printf("\n");
//                    ComputerMove();
//                    ComputerSide = EMPTY;
//                    memset(moveStack, 0, sizeof(moveStack));
//                    moveSearch = 0;
//                    printf("miniMax: %d\n", miniMax(0, -INFINITY, INFINITY, TRUE));
//                    ComputerSide = EMPTY;

            ply = 0;
            moveSearch = 0;
            generateMoves();
            Result = results();
            if (Result == 2) {
                printf("Draw by repetition!\n");
                go = FALSE;
                break;
            } else if (Result == 3) {
                printf("Draw by fifty move rule!\n");
                go = FALSE;
                break;
            } else if (Result == 5) {
                printf("Draw by stalemate!\n");
                go = FALSE;
                break;
            } else if (Result == 4) {
                go = FALSE;
                break;
            }
            continue;
        }
        printf("ececec> ");
        if (scanf("%s", s) == EOF) {
            return 0;
        }
        if (!strcmp(s, "end")) {
            MOVE = FALSE;
            go = FALSE;
            ComputerSide = EMPTY;
            fflush(stdin);
            break;
        }
        if (!strcmp(s, "help")) {
            printf("help - list of commands for ECEC\n");
            printf("show - display the current position\n");
            printf("go - turn on the engine and let it make a move.\n");
            printf("If you enter begin before making a move, engine will be White\n");
            printf("end - turn off the engine and quit the program\n");
            printf("new - start a new game\n");
            printf("To make a move, enter your move in algebraic notation - e.g. e2e4\n");
            continue;
        }


        if (!strcmp(s, "show")) {
            printBoard2();

            int num = 1;
            for (int u = 0; u < hply; u++) {

                if (u % 2 == 0) {
                    printf("%d.", num);
                    num++;
                }

                moveStr(historyStack[u].move.from,
                        historyStack[u].move.to);
                printf(" ");
                if ((u + 1) % 2 == 0) {
                    printf("\n");
                }
            }
            printf("\n\n");
//            moveMade = TRUE;
            continue;
        }

        if (!strcmp(s, "go")) {
            ComputerSide = side_to_move;
            continue;
        }


        if (!strcmp(s, "undo")) {
            if (!hply)
                continue;
            ComputerSide = EMPTY;
            undo();
//            memset(moveStack, 0, sizeof(moveStack));
////            for (auto int i=0; i < moveSearch; i++) {
////                printf("Movestack[i].move.from: %d\n",moveStack[i].move.from);
////                printf("Movestack[i].move.to: %d\n",moveStack[i].move.to);
////            }
            moveSearch = 0;
//                    memset(moveStack, 0, sizeof(moveStack));
            ply = 0;
            generateMoves();
            continue;

        }

        if (!strcmp(s, "new")) {
            ComputerSide = EMPTY;
            initializeBoard();
            continue;
        }


        //parse Move, make sure it's in generated move stack
        for (int b = 0; b < firstMove[ply+1]; b++) {
            printf("from: %d to: %d, pieceType: %d, capture: %d\n",
                   moveStack[b].move.from, moveStack[b].move.to,
                   moveStack[b].move.pieceType, moveStack[b].move.capture);
        }
        move = parseMove(s);

        // if parseMove returns -1, then move is not in move stack from generated moves
        // and is thus illegal
        // else, it is a legal move


        if (move == -1) {
            printf("Not a legal move\n");
            printf("move: %d\n", move);
            moveMade = FALSE;
            continue;
        } else {
            printf("legal move\n");
            printf("move: %d\n", move);
            if (!makeMove(move)) {
                printf("King is in check, illegal move.\n");
                moveMade = FALSE;
                continue;
            }
            printBoard2();
            if (historyStack[hply - 1].move.capture == EMPTY) {
                fiftymoves++;
            } else {
                fiftymoves = 0;
            }

            //once i have made the move, such as e2e4, the movestack is cleared to make space
            //for the other side's generated moves.
//                    memset(moveStack, 0, sizeof(moveStack));

            //moveSearch, which keeps track of the number of possible moves generated in the position
            // for one side is reset to zero. finally, the sides are switched.
            moveSearch = 0;
            checkFound = 0;


            printf("\n");
            // I print the new position, and generate the moves for the new side.
//            printBoard3();
            ply = 0;
            memset(moveStack, 0, sizeof(moveStack));
            printf("historyStack[hply].move.from = %d\n"
                   "historyStack[hply].move.to = %d\n"
                   "historyStack[hply].move.pieceType: %d\n"
                   "historyStack[hply].move.capture: %d\n", historyStack[hply-1].move.from,
                   historyStack[hply-1].move.to, historyStack[hply-1].move.pieceType, historyStack[hply-1].move.capture);

            generateMoves();
//                    for (int g = 0; g < firstMove[ply+1]; g++) {
//                        printf("Capture:\nmoveStack[%d].move.from: %d\n"
//                                      "moveStack[%d].move.to: %d\n"
//                                      "moveStack[%d].move.pieceType: %d\n"
//                                      "moveStack[%d].move.capture: %d\n\n", g, moveStack[g].move.from,
//                                      g, moveStack[g].move.to, g, moveStack[g].move.pieceType,
//                                      g, moveStack[g].move.capture);
//                    }

            Result = results();

            if (Result == 2) {
                printf("Draw by repetition!\n");
            } else if (Result == 3) {
                printf("Draw by fifty move rule!\n");

            } else if (Result == 5) {
                printf("Draw by stalemate!\n");

            } else if (Result == 4) {

            }
        }
    }
}

int main() {
    runGame();
}

int results() {
    int i;
    if (checkRepetition()==2) {
        return 2;
    }
    if (fiftymoves == 100) {

        return 3;
    }
    for (i = 0; i < firstMove[1]; i++) {
        if (makeMove(i)) {
            undo();
            break;
        }
    }
    if (i == firstMove[1]) {
        if (Check(side_to_move)) {
            if (side_to_move == WHITE) {
                printf("Black mates!\n");
                return 4;
            } else {
                printf("White mates!\n");
                return 4;
            }
        } else {

            return 5;
        }

    }

    return 0;
}

