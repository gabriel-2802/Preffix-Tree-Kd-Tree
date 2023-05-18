#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"

void insert_cmd(char *command, trie_t *trie)
{
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	insert_trie(trie, key);
}

void load_cmd(char *command, trie_t *trie)
{
	char *file_name;
	file_name = strtok(command, " ");
	file_name = strtok(NULL, " ");

	FILE *fin = fopen(file_name, "r");
	DIE(!fin, "fopen");

	char *line = NULL;
	size_t buff_len = 0;

	while (getline(&line, &buff_len, fin) != -1) {
		int len = strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		
		len = strlen(line);
		for (int i = 0; i < len; ++i)
			if ((line[i] < 'a' || line[i] > 'z' ))
				line[i] = ' ';


		char *key = strtok(line, " \t");
		while (key) {
			insert_trie(trie, key);
			key = strtok(NULL, " ");
		}	
	}
	fclose(fin);
	free(line);
}

void remove_cmd(char *command, trie_t *trie)
{
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	remove_value(trie->root, key);
}

void find_cmd(char *command, trie_t *trie)
{
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	tnode_t *node = search(key, trie->root, trie->data_size);
	if (node) {
		printf("%s %d\n", (char *)node->value, node->freq);
		
	} else {
		printf("No result\n");
	}

}


void find_words(void *key, tnode_t *root, int k, int *found, int size)
{
	if (!root || k < 0)
		return;	
	if (root->value)
		if ((int)strlen((char *)root->value) > size)
			return;

	if (*(char *)key == '\0' && root->end_word == 1)  {
			printf("%s\n", (char *)root->value);
		*found = 1;
		return;
	}
	
	tnode_t *next_node;

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		next_node = root->children[i];
		if (i == *(char *)key - 'a')
			find_words((void *)((char *)key + 1), next_node, k, found, size);
		else
			find_words((void *)((char *)key + 1), next_node, k - 1, found, size);
		
	}
}

void autocorrect_cmd(char *command, trie_t *trie)
{
	int found = 0;
	char *key, *kk;
	key = strtok(command, " ");
	key = strtok(NULL, " ");
	kk = strtok(NULL, " ");
	int k = atoi(kk);

	find_words(key, trie->root, k, &found, (int)strlen(key));
	if (!found)
		printf("No words found\n");
}


tnode_t *find_first_word(tnode_t *root)
{
	if (!root)
		return NULL;

	if (root->end_word)
		return root;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		tnode_t *next_node = root->children[i];
		if (next_node)
			return find_first_word(next_node);
	}

	return NULL;
}

void print_first_word(tnode_t *pref_node)
{	
	if (pref_node->end_word) {
		printf("%s\n", (char *)pref_node->value);
		return;
	}
	
	tnode_t *print_first_word = find_first_word(pref_node);
	printf("%s\n", (char *)print_first_word->value);
}

void find_shortest_word(tnode_t *pref_node, char *word, int *min_size)
{
	if (pref_node->end_word && (int)strlen((char *)pref_node->value) < *min_size) {
		*min_size = strlen((char *)pref_node->value);
		strcpy(word, (char *)pref_node->value);
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		tnode_t *next_node = pref_node->children[i];
		if (next_node)
			find_shortest_word(next_node, word, min_size);
	}
}

void print_shortest_word(tnode_t *pref_node)
{
	char *word = malloc(MAX_WORD_SIZE);
	DIE(!word, "malloc word");

	int min_size = MAX_WORD_SIZE;
	find_shortest_word(pref_node, word, &min_size);

	if (min_size == MAX_WORD_SIZE)
		printf("No words found\n");
	else 
		printf("%s\n", word);
	free(word);
}

void find_most_freq_word(tnode_t *pref_node, char *word, int *freq)
{
	if (pref_node->end_word && pref_node->freq > *freq) {
		*freq = pref_node->freq;
		strcpy(word, (char *)pref_node->value);
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		tnode_t *next_node = pref_node->children[i];
		if (next_node)
			find_most_freq_word(next_node, word, freq);
	}
}

void print_most_freq_word(tnode_t *pref_node)
{
	char *word = malloc(MAX_WORD_SIZE);
	DIE(!word, "malloc word");
	int freq = -1;

	find_most_freq_word(pref_node, word, &freq);
	if (freq != -1)
		printf("%s\n", word);
	else
		printf("No words found\n");
	
	free(word);
}

void autocomplete_cmd(char *command, trie_t *trie)
{
	char *key, *criterium;
	key = strtok(command, " ");
	key = strtok(NULL, " ");
	criterium = strtok(NULL, " ");
	int crit = atoi(criterium);

	tnode_t *pref_node = search_prefix(key, trie->root);
	if (!pref_node) {
		printf("No words found\n");

		if (!crit) {
			printf("No words found\n");
			printf("No words found\n");
		}
		return;
	}

	switch (crit) {
		case 0:
			print_first_word(pref_node);
			print_shortest_word(pref_node);
			print_most_freq_word(pref_node);
			break;
		case 1:
			print_first_word(pref_node);
			break;
		case 2:
			print_shortest_word(pref_node);
			break;
		case 3:	
			print_most_freq_word(pref_node);
			break;
	}
	
}
