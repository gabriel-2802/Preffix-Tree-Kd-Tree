#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"

void insert_cmd(char *command, trie_t *trie);

void load_cmd(char *command, trie_t *trie);

void remove_cmd(char *command, trie_t *trie);

void find_cmd(char *command, trie_t *trie);

void find_words(void *key, tnode_t *root, int k, int *found);


void autocorrect_cmd(char *command, trie_t *trie);