# Makefile for mem memory system
# muh, CSE 374, sp21

CC = gcc
CARGS = -Wall -std=c11

all: bench

# basic build
bench: bench.o memory.o
	$(CC) $(CARGS) -o bench $^

# object files
bench.o: bench.c mem.h
	$(CC) $(CARGS) -c bench.c

# Target to run the bench test program with default parameters
test: bench
	./bench

# Target to remove bench.o files, bench executable, and emacs backup files
clean:
	rm -f bench bench.o *~

