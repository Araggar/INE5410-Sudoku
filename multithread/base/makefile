BIN=sudoku
CC=gcc
LD=-lpthread
FLAGS= -g -O3

all: sudoku.c
	$(CC) -o $(BIN) sudoku.c stack.c $(LD) $(FLAGS)

clean:
	rm -rf $(BIN) *~
