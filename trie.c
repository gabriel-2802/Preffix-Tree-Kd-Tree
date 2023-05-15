#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"

tnode_t *node_create()
{
	tnode_t *node = malloc(sizeof(tnode_t));
	DIE(!node, "malloc node");

	node->value = NULL;
	node->end_word = 0;
	node->freq = 0;
	node->n_children = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->children[i] = NULL;

	return node;
}

trie_t *trie_create(int data_size)
{
	trie_t *trie = malloc(sizeof(trie_t));
	DIE(!trie, "malloc trie");

	trie->root = NULL;
	trie->size = 0;
	trie->data_size = data_size;

	trie->root = node_create();

	return trie;
}

tnode_t *search(void *key, tnode_t *root, int data_size)
{
	if (!root)
		return NULL;
	
	if (*(char *)key == '\0' && root->end_word == 1)
		return root;
	
	if (*(char *)key == '\0' && root->end_word == 0)
		return NULL;
	
	tnode_t *next_node = root->children[*(char *)key - 'a'];
	if (!next_node)
		return NULL;

	return search((void *)((char *)key + 1), next_node, data_size);
}

void insert(tnode_t *node, void *key, void *value, int data_size)
{
	if (*(char *)key == '\0') {
		node->value = malloc(data_size);
		DIE(!node->value, "malloc value");

		memcpy(node->value, value, data_size);
		node->end_word = 1;
		node->freq++;
		return;
	}

	tnode_t *next_node = node->children[*(char *)key - 'a'];

	if (!next_node) {
		node->children[*(char *)key - 'a'] = node_create();
		node->n_children++;

		next_node = node->children[*(char *)key - 'a'];
	}

	void *value_copy = malloc(data_size);
    DIE(!value_copy, "malloc value_copy");
    memcpy(value_copy, value, data_size);

	insert(next_node, (void *)((char *)key + 1), value_copy, data_size);

	free(value_copy);
}

void insert_trie(trie_t *trie, void *key)
{
	
	char *value = malloc(trie->data_size);
	DIE(!value, "malloc value");
	strcpy(value, key);

	tnode_t *searched_node  = search(value, trie->root, trie->data_size);
	if (!searched_node) {
		insert(trie->root, key, value, trie->data_size);
		trie->size++;
	} else {
		searched_node->freq++;
	}

	free(value);
}

void delete_node(tnode_t *node)
{
	if (node->value) {
		free(node->value);
        node->value = NULL;
    }
    if (node)
	    free(node);
}

int remove_value(tnode_t *node, void *key)
{
	if (*(char *)key == '\0') {
		free(node->value);
		node->value = NULL;

		if (node->end_word) {
			node->end_word = 0;
			return node->n_children == 0;
		}

		return 0;
	}

	tnode_t *next_node = node->children[*(char *)key - 'a'];

	if (next_node && (remove_value(next_node, (void *)((char *)key + 1)) == 1)) {
		node->n_children--;
		delete_node(next_node);
		node->children[*(char *)key - 'a'] = NULL;  // set the child pointer to NULL

		if (node->end_word == 0 && node->n_children == 0)
			return 1;
	}

	return 0;
}

void free_node(tnode_t *node)
{
	if (!node)
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		free_node(node->children[i]);

	delete_node(node);
}

void free_trie(trie_t *trie)
{
	if (!trie)
		return;
	
	free_node(trie->root);

	free(trie);
}

