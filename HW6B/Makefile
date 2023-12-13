# Makefile for mem memory system
# Christopher Andrade
# 12/13/2023

CC = gcc
CARGS = -Wall -std=c11

all: bench

# basic build
bench: bench.o getmem.o freemem.o mem_utils.o
	$(CC) $(CARGS) -o bench $^

# object files
getmem.o: getmem.c mem.h mem_impl.h
	$(CC) $(CARGS) -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	$(CC) $(CARGS) -c freemem.c

mem_utils.o: mem_utils.c mem.h mem_impl.h
	$(CC) $(CARGS) -c mem_utils.c

debug: CARGS += -g -D DEBUG
debug: bench

noassert: CARGS += -D NDEBUG
noassert: bench

test: debug
	./bench
	./bench 5
	./bench 50000 10
	./bench 2 10 100
	./bench 18 5 100 16
	./bench 3 100 100 500 2000 1
	./bench 4 50 50 500 2000 1
	./bench 1 50 50 500 2000 1

clean:
	rm -rf bench freemem.o getmem.o mem_utils.o *~
