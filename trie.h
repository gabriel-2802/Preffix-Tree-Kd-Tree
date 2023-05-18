#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define ALPHABET_SIZE 26
#define MAX_WORD_SIZE 100

typedef struct tnode_t tnode_t;
typedef struct trie_t trie_t;

struct tnode_t {
	void *value;
	int end_word;
	tnode_t *children[ALPHABET_SIZE];
	int freq;
	int n_children;

};

struct trie_t {
	tnode_t *root;

	/* number of keys */
	int size;
	int data_size;
};

tnode_t *node_create();

trie_t *trie_create(int data_size);

tnode_t *search(void *key, tnode_t *root, int data_size);

tnode_t *search_prefix(char *key, tnode_t *root);

void insert(tnode_t *node, void *key, void *value, int data_size);

void insert_trie(trie_t *trie, void *key);

void delete_node(tnode_t *node);

int remove_value(tnode_t *node, void *key);

void free_node(tnode_t *node);

void free_trie(trie_t *trie);