#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/timeb.h>
#include "defs.h"
#include "globals.h"
#include "protoypes.h"

int end = FALSE;
int timeOK;

int timeElapsed() {
    struct timeb time;
    //fetch time
    ftime(&time);
    timeOK = TRUE;
    return (time.time * 1000);
}


int runGame() {
    ComputerSide = NONE;
    initializeBoard();
    generateMoves();
    max_time = 1 << 20;
    // this is the string input from the user
    char s[256];
    SDL_Event event;
    int i;
    int increment = 7;
    int Result = 0;

    printf("Welcome to the Extra Credit Engine of Chess by Elias Cannesson, \n");
    printf("ECECEC. Enter 'help' for a list of commands to use the engine. \n");

    while (go) {

            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        go = FALSE;
                        break;
                    default:
                        break;
                }
            }

            while (MOVE) {
                if (side_to_move == ComputerSide) {
                    ComputerPlay();

                    makeMove(triangularArray[0][0].index);

                    ply = 0;
                    moveSearch = 0;
                    generateMoves();
                    Result = results();
                    if (Result == 2) {
                        printf("Draw by repetition!\n");
                        MOVE = FALSE;
                        moveMade = TRUE;
                        break;
                    } else if (Result == 3) {
                        printf("Draw by fifty move rule!\n");
                        MOVE = FALSE;
                        moveMade = TRUE;
                        break;
                    } else if (Result == 5) {
                        printf("Draw by stalemate!\n");
                        MOVE = FALSE;
                        moveMade = TRUE;
                        break;
                    } else if (Result == 4) {
                        MOVE = FALSE;
                        moveMade = TRUE;
                        break;
                    }
                    moveMade = TRUE;
                    MOVE = FALSE;
                    break;
                }
                printf("ECECEC---");

                if (scanf("%s", s) == EOF) {
                    return 0;
                }
                printf("s: %s\n", s);
                if (!strcmp(s, "end")) {
                    MOVE = FALSE;
                    ComputerSide = EMPTY;
                    moveMade = TRUE;

                    end = TRUE;
                    go = FALSE;
                }
                if (!strcmp(s, "help")) {
                    printf("help - list of commands for ECECEC\n");
                    printf("show - display the current position\n");

                    printf("go - turn on the engine and let it make a move.\n");
                    printf("If you enter begin before making a move, engine will be White\n");
                    printf("end - turn off the engine and quit the program\n");
                    printf("new - start a new game\n");
                    printf("To make a move, enter your move in algebraic notation - e.g. e2e4\n");
                    continue;
                }

                if (!strcmp(s, "show")) {
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
                    moveMade = TRUE;
                    break;

                }
                printf("S: %s\n", s);
                if (!strcmp(s, "go")) {
                    ComputerSide = side_to_move;
                    continue;
                }

                if (!strcmp(s, "undo")) {
                    if (!hply)
                        continue;
                    ComputerSide = EMPTY;
                    undo();
                    moveSearch = 0;
                    ply = 0;
                    generateMoves();
                    moveMade = TRUE;
                    MOVE = FALSE;
                    continue;
                }
                if (!strcmp(s, "new")) {
                    ComputerSide = EMPTY;
                    initializeBoard();
                    continue;
                }

                printf("castle: %d\n", castle);
                printf("historyStack[hply].castle: %d\n", historyStack[hply].castle);
                //parse Move, make sure it's in generated move stack
                move = parseMove(s);

                if (move == -1) {
                    printf("Not a legal move\n");
                    printf("move: %d\n", move);
                    moveMade = FALSE;
                    continue;
                } else {
                    if (!makeMove(move)) {
                        printf("King is in check, illegal move.\n");
                        moveMade = FALSE;
                        continue;
                    }
                    if (historyStack[hply-1].move.capture == EMPTY) {
                        fiftymoves++;
                    } else {
                        fiftymoves = 0;
                    }

                    moveSearch = 0;
                    printf("\n");

                    ply = 0;
                    generateMoves();
                    moveMade = TRUE;
                    MOVE = FALSE;
                    results();
            }
        }
        if (moveMade) {

            SDL_SetRenderDrawColor(render, 81, 129, 164, 255);
            SDL_RenderClear(render);


            // render
            SDL_Rect texture_destination;

            texture_destination.w = 54;
            texture_destination.h = 54;

            int startPos = 0;
            for (int y = 0; y < 8; y++) {
                for (int x = startPos; x < 8; x+=2) {
                    SDL_Rect rect;
                    rect.x = x * 64 + 32;
                    rect.y = y * 64;
                    rect.w = 64;
                    rect.h = 64;
                    SDL_SetRenderDrawColor(render, 220, 220, 220, 255);
                    SDL_RenderFillRect(render, &rect);
                }
                startPos = 1 - startPos;
            }
            texture_destination.x = 36;
            texture_destination.y = 6;

            for (i = 0; i < 64; i++) {
                if (color[i] == BLACK) {
                    switch (pieces[i]) {
                        case PAWN:
                            SDL_RenderCopy(render, image_textures[0], NULL, &texture_destination);
                            break;
                        case KING:
                            SDL_RenderCopy(render, image_textures[2], NULL, &texture_destination);
                            break;
                        case KNIGHT:
                            SDL_RenderCopy(render, image_textures[4], NULL, &texture_destination);
                            break;
                        case BISHOP:
                            SDL_RenderCopy(render, image_textures[6], NULL, &texture_destination);
                            break;
                        case ROOK:
                            SDL_RenderCopy(render, image_textures[8], NULL, &texture_destination);
                            break;
                        case QUEEN:
                            SDL_RenderCopy(render, image_textures[10], NULL, &texture_destination);
                            break;
                    }

                } else if (color[i] == WHITE) {
                    switch (pieces[i]) {
                        case PAWN:
                            SDL_RenderCopy(render, image_textures[1], NULL, &texture_destination);
                            break;
                        case KING:
                            SDL_RenderCopy(render, image_textures[3], NULL, &texture_destination);
                            break;
                        case KNIGHT:
                            SDL_RenderCopy(render, image_textures[5], NULL, &texture_destination);
                            break;
                        case BISHOP:
                            SDL_RenderCopy(render, image_textures[7], NULL, &texture_destination);
                            break;
                        case ROOK:
                            SDL_RenderCopy(render, image_textures[9], NULL, &texture_destination);
                            break;
                        case QUEEN:
                            SDL_RenderCopy(render, image_textures[11], NULL, &texture_destination);
                            break;
                    }
                }
                if (i == increment) {
                    texture_destination.y += 64;
                    texture_destination.x = 36;
                    increment+=8;
                    continue;
                }
                texture_destination.x += 64;
            }

            SDL_RenderDrawLine(render, 32, 0, 32, 512);
            SDL_RenderDrawLine(render, 32, 512, 544, 512);
            //display
            SDL_RenderPresent(render);
            increment = 7;
            moveMade = FALSE;
            MOVE = TRUE;
            if (end == TRUE) {
                go = FALSE;
            }
        }
        //clear

        // update

        if (end == TRUE) {
            for (int j = 0; j < 12; j++) {
                SDL_DestroyTexture(image_textures[i]);
            }
            for (i = 0; i < 12; i++) {
                SDL_FreeSurface(imagePieces[i]);
            }
            SDL_DestroyRenderer(render);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            go = FALSE;
            printf("quit everything\n");
            return 0;
        }


    }

    for (int j = 0; j < 12; j++) {
        SDL_DestroyTexture(image_textures[i]);
    }
    for (i = 0; i < 12; i++) {
        SDL_FreeSurface(imagePieces[i]);
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    go = FALSE;
    printf("quit everything\n");
    return 0;
}




int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
//Image Stuff
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    runGame();
}

int results() {
    int i;
    if (fiftymoves == 100) {
        return 3;
    }
    for (i = 0; i < movesInSearch[1]; i++) {
        if (makeMove(i)) {
            undo();
            break;
        }
    }
    if (i == movesInSearch[1]) {
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

