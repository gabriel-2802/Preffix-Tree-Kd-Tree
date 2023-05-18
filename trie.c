#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "aux_functions.h"
#include "trie.h"

tnode_t *node_create()
{
	tnode_t *node = malloc(sizeof(tnode_t));
	DIE(!node, "malloc node");

	/* initalizam valorile */
	node->value = NULL;
	node->end_word = 0;
	node->freq = 0;
	node->n_children = 0;

	/* initializam vectorul de copii cu NULL */
	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->children[i] = NULL;

	return node;
}


trie_t *trie_create(int data_size)
{
	trie_t *trie = malloc(sizeof(trie_t));
	DIE(!trie, "malloc trie");

	/* initializam valorile */
	trie->root = NULL;
	trie->size = 0;
	trie->data_size = data_size;
	/* cream radacina care va avea 26 de copii */
	trie->root = node_create();

	return trie;
}

tnode_t *search(void *key, tnode_t *root, int data_size)
{
	if (!root)
		return NULL;
	
	/* daca am ajuns la finalul cuvantului si nodul este sfarsit de
	cuvant, returnam nodul */
	if (*(char *)key == '\0' && root->end_word == 1)
		return root;
	
	/* daca am ajuns la finalul cuvantului si nodul nu este sfarsit
	de cuvant, returnam NULL */
	if (*(char *)key == '\0' && root->end_word == 0)
		return NULL;
	
	/* daca nu am ajuns la finalul cuvantului, cautam in copilul nodului 
	corespunzator primei litere din cheie*/
	tnode_t *next_node = root->children[*(char *)key - 'a'];
	if (!next_node)
		return NULL;

	/* reapelam search din copil, pornind din a doua litera a cheii */
	return search((void *)((char *)key + 1), next_node, data_size);
}

tnode_t *search_prefix(char *key, tnode_t *root)
{
	if (!root)
		return NULL;
	
	/* daca am ajuns la finalul cuvantului, returnam nodul */
	if (*(char *)key == '\0')
		return root;
	
	/* daca nu am ajuns la finalul cuvantului, cautam in copilul nodului
	corespunzator primei litere din cheie */
	tnode_t *next_node = root->children[*(char *)key - 'a'];
	if (!next_node)
		return NULL;

	return search_prefix((void *)((char *)key + 1), next_node);
}

void insert(tnode_t *node, void *key, void *value, int data_size)
{
	/* daca am ajuns la finalul cuvantului, setam valoarea nodului */
	if (*(char *)key == '\0') {
		node->value = malloc(data_size);
		DIE(!node->value, "malloc value");

		memcpy(node->value, value, data_size);
		node->end_word = 1;
		node->freq++;
		return;
	}

	/* daca nu am ajuns la finalul cuvantului, cautam in copilul nodului
	corespunzator primei litere din cheie */
	tnode_t *next_node = node->children[*(char *)key - 'a'];

	/* daca nu exista copilul, il cream */
	if (!next_node) {
		node->children[*(char *)key - 'a'] = node_create();
		node->n_children++;

		/* next node devine copilul nodului nou creat */
		next_node = node->children[*(char *)key - 'a'];
	}

	insert(next_node, (void *)((char *)key + 1), value, data_size);
}

void insert_trie(trie_t *trie, void *key)
{
	
	char *value = malloc(trie->data_size);
	DIE(!value, "malloc value");
	strcpy(value, key);

	/* daca valoarea nu exista in trie, o inseram */
	tnode_t *searched_node  = search(value, trie->root, trie->data_size);
	if (!searched_node) {
		insert(trie->root, key, value, trie->data_size);
		trie->size++;
	} else {
		/* daca valoarea exista, incrementam frecventa */
		searched_node->freq++;
	}

	free(value);
}

void delete_node(tnode_t *node)
{	
	if (node) {
		free(node->value);
		node->value = NULL;
		free(node);
	}
}

int remove_value(tnode_t *node, void *key)
{
	
	/* daca am ajuns la finalul cuvantului, stergem valoarea nodului */
	if (*(char *)key == '\0') {
		free(node->value);
		node->value = NULL;

		/* daca nodul este sfarsit de cuvant, reinitializam end_word */
		if (node->end_word) {
			node->end_word = 0;
			return node->n_children == 0;
		}

		return 0;
	}

	tnode_t *next_node = node->children[*(char *)key - 'a'];

	/* daca urm nod exista si este o frunza, il stergem */
	if (next_node && (remove_value(next_node, (void *)((char *)key + 1)) == 1)) {
		node->n_children--;
		delete_node(next_node);

		/* setam copilul nodului curent NULL */
		node->children[*(char *)key - 'a'] = NULL; 

		/* daca nodul curent nu este sfarsit de cuvant si nu are copii,
		returnam 1 */
		if (node->end_word == 0 && node->n_children == 0)
			return 1;
	}

	return 0;
}

void free_node(tnode_t *node)
{
	if (!node)
		return;

	/* recursiv, stergem toate nodurile */
	for (int i = 0; i < ALPHABET_SIZE; i++)
		free_node(node->children[i]);

	/* eliberam memoria nodului */
	delete_node(node);
}

void free_trie(trie_t *trie)
{
	if (!trie)
		return;
	
	free_node(trie->root);
	free(trie);
}

