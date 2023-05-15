#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"
#include "mk_commands.h"


tnode_t *search_prefix(char *key, tnode_t *root)
{
	if (!root)
		return NULL;
	
	if (*(char *)key == '\0')
		return root;
	
	tnode_t *next_node = root->children[*(char *)key - 'a'];
	if (!next_node)
		return NULL;

	return search_prefix((void *)((char *)key + 1), next_node);
}

tnode_t *search_smallest_word(tnode_t *root)
{
	if (!root)
		return NULL;

	if (root->end_word)
		return root;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		tnode_t *next_node = root->children[i];
		if (next_node)
			return search_smallest_word(next_node);
	}

	return NULL;
}

void smallest_word(tnode_t *pref_node)
{	
	if (pref_node->end_word) {
		printf("%s\n", (char *)pref_node->value);
		return;
	}
	
	tnode_t *smallest_word = search_smallest_word(pref_node);
	printf("%s\n", (char *)smallest_word->value);
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

void shortest_word(tnode_t *pref_node)
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

void most_freq_word(tnode_t *pref_node)
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
			smallest_word(pref_node);
			shortest_word(pref_node);
			most_freq_word(pref_node);
			break;
		case 1:
			smallest_word(pref_node);
			break;
		case 2:
			shortest_word(pref_node);
			break;
		case 3:	
			most_freq_word(pref_node);
			break;
		
	}
	
}

int main(void)
{	
	trie_t *trie = trie_create(sizeof(char) * MAX_WORD_SIZE);
	char *cmd_string;
	int cmd = -1, done = 0;

	while (1) {
		cmd_string = read_cmd();
		command(&cmd, cmd_string);

		switch (cmd) {
		case 1:
			insert_cmd(cmd_string, trie);
			break;
		case 2:
			load_cmd(cmd_string, trie);
			break;
		case 3:
			remove_cmd(cmd_string, trie);
			break;
		case 4:
			autocorrect_cmd(cmd_string, trie);
			break;
		case 5:
			autocomplete_cmd(cmd_string, trie);
			break;
		case 6:
			free_trie(trie);
			done = 1;
			break;
		case 7:
			find_cmd(cmd_string, trie);
			break;
		default:
			printf("Invalid command\n");
			break;
		}

		if (cmd_string)
			free(cmd_string);

		if (done)
			break;

	}

	return 0;
}
