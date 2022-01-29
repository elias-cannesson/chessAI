# -*- Makefile -*-
CC := clang
FLAGS := -std=c11 -g

all: chessAI

#chessAI: body_chess2.o globals.o  move.o hash.o board2.o gen.o \
#			eval.o search.o gen2.o defs.h globals.h protoypes.h
#	$(CC) body_chess2.o globals.o move.o board2.o hash.o gen.o eval.o \
#			search.o gen2.o -o chessAI -lSDL2 -lSDL2_image

chessAI: body_chess.o globals.o pvtable.o pieceData.o ruleData.o move.o board.o movegen.o eval.o search.o capgen.o defs.h globals.h protoypes.h
	$(CC) body_chess.o globals.o pvtable.o pieceData.o ruleData.o move.o board.o movegen.o eval.o \
			search.o capgen.o -o chessAI -lSDL2 -lSDL2_image

body_chess.o: body_chess.c globals.h defs.h protoypes.h
	$(CC) $(FLAGS) -c body_chess.c

board.o: board.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c board.c

globals.o: globals.c globals.h defs.h protoypes.h
	$(CC) $(FLAGS) -c globals.c

pvtable.o: pvtable.c globals.h defs.h protoypes.h
	$(CC) $(FLAGS) -c pvtable.c

pieceData.o: pieceData.c globals.h defs.h protoypes.h
	$(CC) $(FLAGS) -c pieceData.c

ruleData.o: ruleData.c globals.h defs.h protoypes.h
	$(CC) $(FLAGS) -c ruleData.c

move.o: move.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c move.c

movegen.o: movegen.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c movegen.c

eval.o: eval.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c eval.c

search.o: search.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c search.c

capgen.o: capgen.c defs.h globals.h protoypes.h
	$(CC) $(FLAGS) -c capgen.c




