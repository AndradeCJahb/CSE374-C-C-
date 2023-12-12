# Makefile for mem memory system
# muh, CSE 374, sp21

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

clean:
	rm -rf bench freemem.o getmem.o mem_utils.o *~
