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
	/* 1 daca nodul este sfarsit de cuvant, 0 altfel */
	int end_word;
	tnode_t *children[ALPHABET_SIZE];
	/* frecventa cuvantului */
	int freq;
	/* numarul de copii */
	int n_children;

};

struct trie_t {
	tnode_t *root;
	/* nr de cuvinte  */
	int size;
	int data_size;
};

/* creeaza nodul nou 
 * @return: nodul nou creat 
*/
tnode_t *node_create();

/* creeaza trie-ul
 * @param1: dimensiunea datelor din noduri
 * @return: trie-ul nou creat
*/
trie_t *trie_create(int data_size);

/* cauta un cuvant in trie
 * @param1: cheia de cautat
 * @param2: nodul de la care incepe cautarea
 * @param3: dimensiunea datelor din noduri
 * @return: nodul in care se termina cuvantul, NULL altfel
 */
tnode_t *search(void *key, tnode_t *root, int data_size);

/* cauta un prefix in trie
 * @param1: cheia de cautat
 * @param2: nodul de la care incepe cautarea
 * @return: nodul in care se termina pref, NULL altfel
 */
tnode_t *search_prefix(char *key, tnode_t *root);

/* insereaza un nod in trie, inital key == value
 * @param1: nodul in care se insereaza
 * @param2: cheia dupa care se insereaza
 * @param3: valoarea de inserat 
 * @param4: dimensiunea datelor din noduri
 * @return: nodul in care se termina pref, NULL altfel
 */
void insert(tnode_t *node, void *key, void *value, int data_size);

/* insereaza un nod in trie, apeleaza insert
 * @param1: arborele
 * @param2: cheia dupa care se insereaza
 */
void insert_trie(trie_t *trie, void *key);

/* sterge un nod si cheia sa
 * @params1: npdul de sters
 */
void delete_node(tnode_t *node);

/* sterge un nod din trie (cuvant, cheie)
 * @param1: nodul de sters
 * @param2: cheia de sters
 * @return: 1 daca nodul de sters este o frunza
 */
int remove_value(tnode_t *node, void *key);

/* sterge un nod si toti copii sai)
 * @param1: arborele
 */
void free_node(tnode_t *node);

/* elibereaza memoria ocupata de trie
 * @param1: arborele
 */
void free_trie(trie_t *trie);