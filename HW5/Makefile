CC = gcc
CFLAGS = -Wall -std=c11

all: t9

t9: trie.o tnine.o
	$(CC) $(CFLAGS) -o t9 trie.o tnine.o

trie.o: trie.c trienode.h
	$(CC) $(CFLAGS) -c trie.c

tnine.o: tnine.c trienode.h
	$(CC) $(CFLAGS) -c tnine.c

clean:
	rm -f t9 *.o
