# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpedantic -std=c99 -O0 -g -ggdb

# define targets
TARGETS=kNN mk

#define object-files
OBJ=mk.o kNN.o aux_functions.o mk_commands.o trie.o

build: $(TARGETS)

mk: mk.o aux_functions.o mk_commands.o trie.o
	$(CC) $(CFLAGS) $^ -o $@

kNN: kNN.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_MarcelPetrescu_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJ)

.PHONY: pack clean
