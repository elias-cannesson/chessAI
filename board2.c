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
            printf("%c ", piece_char[pieces[i]-1]);
        } else if (color[i] == BLACK) {
            printf("%c ", tolower(piece_char[pieces[i]-1]));
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
        printf("Hash: %d\n\n", hash);

}

void initializeBoard() {
    int i;
    side_to_move = WHITE;
    other_side = BLACK;

    enPassant = -1;
    bool_enPassant = FALSE;
    ply = 0;
    hply = 0;
    fiftymoves = 0;
    promoted = 0;
    repetition = 0;
    checkFound = 0;
    castle = 15;
    moveSearch = 0;

    check = 0;

    go = TRUE;
    moveMade = TRUE;
    MOVE = TRUE;
    firstMove[0] = 0;

    set_hash();

    printf("Hash: %d\n", hash);



    for (i = 0; i < 64; i++) {
        pieces[i] = init_pieces[i];
        color[i] = init_color[i];
    }

//    for (i = 0; i < 64; i++) {
//        pieces[i] = enPassantTest[i];
//        color[i] = enPassantTestColor[i];
//    }

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
                printf("| %c ", piece_char[pieces[i]-1]);
            } else {
                printf("||%c|", piece_char[pieces[i]-1]);
            }

        } else if (color[i] == BLACK) {
            if (j % 2 == 0) {
                printf("| %c ", tolower(piece_char[pieces[i]-1]));
            } else {
                printf("||%c|", tolower(piece_char[pieces[i]-1]));
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
    printf("Hash: %d\n\n", hash);
}


