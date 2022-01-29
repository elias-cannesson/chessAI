#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "globals.h"
#include "defs.h"
#include "protoypes.h"

void printBoard() {
    auto int i;
    int rank = 8;
    printf("\n    Chess Board\n");

    for (i = 0; i < 64; i++) {

        if (i % 8 == 0) {
            printf("\n");
            printf("%d  ", rank);
            rank--;

        }
        if (color[i] == WHITE) {
            printf("%c ", pieceString[pieces[i]-1]);
        } else if (color[i] == BLACK) {
            printf("%c ", tolower(pieceString[pieces[i]-1]));
        } else {
            printf(". ");
        }
    }
        printf("\n\n   a b c d e f g h\n");
        printf("\n");
        if (side_to_move == WHITE) {
            printf("    White to move\n\n");
        } else {
            printf("    Black to move\n\n");
        }

        printf("En Passant Square: %d\n", enPassant);

}

void initializeBoard() {
    int i;
    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_ISCENTERED(200),
                              SDL_WINDOWPOS_ISCENTERED(200), 544, 544, SDL_WINDOW_SHOWN);

    render = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    for (i = 0; i < 12; i++) {
        switch(i) {
            case 0:
                imagePieces[0] = IMG_LoadTyped_RW(SDL_RWFromFile("blackPawn.png", "rb"), 1, "png");
                break;
            case 1:
                imagePieces[1] = IMG_LoadTyped_RW(SDL_RWFromFile("whitePawn.png", "rb"), 1, "png");
                break;
            case 2:
                imagePieces[2] = IMG_LoadTyped_RW(SDL_RWFromFile("blackKing.png", "rb"), 1, "png");
                break;
            case 3:
                imagePieces[3] = IMG_LoadTyped_RW(SDL_RWFromFile("whiteKing.png", "rb"), 1, "png");
                break;
            case 4:
                imagePieces[4] = IMG_LoadTyped_RW(SDL_RWFromFile("knightBlack.png", "rb"), 1, "png");
                break;
            case 5:
                imagePieces[5] = IMG_LoadTyped_RW(SDL_RWFromFile("knightWhite.png", "rb"), 1, "png");
                break;
            case 6:
                imagePieces[6] = IMG_LoadTyped_RW(SDL_RWFromFile("blackBishop.png", "rb"), 1, "png");
                break;
            case 7:
                imagePieces[7] = IMG_LoadTyped_RW(SDL_RWFromFile("whiteBishop.png", "rb"), 1, "png");
                break;
            case 8:
                imagePieces[8] = IMG_LoadTyped_RW(SDL_RWFromFile("blackRook.png", "rb"), 1, "png");
                break;
            case 9:
                imagePieces[9] = IMG_LoadTyped_RW(SDL_RWFromFile("whiteRook.png", "rb"), 1, "png");
                break;
            case 10:
                imagePieces[10] = IMG_LoadTyped_RW(SDL_RWFromFile("blackQueen.png", "rb"), 1, "png");
                break;
            case 11:
                imagePieces[11] = IMG_LoadTyped_RW(SDL_RWFromFile("whiteQueen.png", "rb"), 1, "png");
                break;
            default:
                printf("Error in initializing imagePieces.\n");
                break;
        }

    }
    for (i = 0; i < 12; i++) {
        switch(i) {
            case 0:
                image_textures[0] = SDL_CreateTextureFromSurface(render, imagePieces[0]);
                break;
            case 1:
                image_textures[1] = SDL_CreateTextureFromSurface(render, imagePieces[1]);
                break;
            case 2:
                image_textures[2] = SDL_CreateTextureFromSurface(render, imagePieces[2]);
                break;
            case 3:
                image_textures[3] = SDL_CreateTextureFromSurface(render, imagePieces[3]);
                break;
            case 4:
                image_textures[4] = SDL_CreateTextureFromSurface(render, imagePieces[4]);
                break;
            case 5:
                image_textures[5] = SDL_CreateTextureFromSurface(render, imagePieces[5]);
                break;
            case 6:
                image_textures[6] = SDL_CreateTextureFromSurface(render, imagePieces[6]);
                break;
            case 7:
                image_textures[7] = SDL_CreateTextureFromSurface(render, imagePieces[7]);
                break;
            case 8:
                image_textures[8] = SDL_CreateTextureFromSurface(render, imagePieces[8]);
                break;
            case 9:
                image_textures[9] = SDL_CreateTextureFromSurface(render, imagePieces[9]);
                break;
            case 10:
                image_textures[10] = SDL_CreateTextureFromSurface(render, imagePieces[10]);
                break;
            case 11:
                image_textures[11] = SDL_CreateTextureFromSurface(render, imagePieces[11]);
                break;
            default:
                printf("Error in initializing image_textures.\n");
                break;
        }
    }


    side_to_move = WHITE;
    other_side = BLACK;

    enPassant = -1;
    ply = 0;
    hply = 0;
    fiftymoves = 0;
    promoted = 0;
    repetition = 0;
    castle = 15;
    moveSearch = 0;
    check = 0;

    go = TRUE;
    moveMade = TRUE;
    MOVE = FALSE;
    movesInSearch[0] = 0;

    for (i = 0; i < 64; i++) {
        pieces[i] = initial_pieces[i];
        color[i] = initial_color[i];
    }

}

void printBoard2() {
    auto int i, j;
    j = 1;
    int rank = 8;
    int increment = 7;

    for (i = 0; i < 64; i++) {
        if ((i % 8) == 0) {
            j++;
            printf("\n+---+---+---+---+---+---+---+---+\n");

        }
        if (color[i] == WHITE) {
            if (j % 2 == 0) {
                printf("| %c ", pieceString[pieces[i]-1]);
            } else {
                printf("||%c|", pieceString[pieces[i]-1]);
            }

        } else if (color[i] == BLACK) {
            if (j % 2 == 0) {
                printf("| %c ", tolower(pieceString[pieces[i]-1]));
            } else {
                printf("||%c|", tolower(pieceString[pieces[i]-1]));
            }

        } else {
            if (j % 2 == 0) {
                printf("|   ");
            } else {
                printf("||||");
            }

        }

        if (i == increment) {
            printf("| %d", rank);
            increment+=8;
            rank--;
        }
        j++;
    }
    printf("\n+---+---+---+---+---+---+---+---+\n");
      printf("  a   b   c   d   e   f   g   h\n\n");
    if (side_to_move == WHITE) {
        printf("    White to move\n\n");
    } else {
        printf("    Black to move\n\n");
    }

    printf("En Passant Square: %d\n", enPassant);
}



