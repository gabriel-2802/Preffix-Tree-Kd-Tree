# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpedantic -std=c99 -O0 -g -ggdb

# define targets
TARGETS=kNN mk

#define object-files
OBJ=mk.o kNN.o aux_functions.o mk_commands.o trie.o kd_tree.o kd_commands.o kd_aux.o

build: $(TARGETS)

mk: mk.o aux_functions.o mk_commands.o trie.o
	$(CC) $(CFLAGS) $^ -o $@

kNN: kNN.o kd_tree.o kd_commands.o aux_functions.o kd_aux.o
	$(CC) $(CFLAGS) $^ -lm -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_MarcelPetrescu_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJ)

.PHONY: pack clean
