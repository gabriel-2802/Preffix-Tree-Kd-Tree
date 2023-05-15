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
		
		char *key = strtok(line, " ");
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
		printf("%s\n", (char *)node->value);
		
	} else {
		printf("No result\n");
	}

}


void find_words(void *key, tnode_t *root, int k, int *found)
{
	if (!root || k < 0)
		return;	
	
	if (*(char *)key == '\0' && root->end_word == 1) {
		*found = 1;
		printf("%s\n", (char *)root->value);
	}
	
	tnode_t *next_node;

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		next_node = root->children[i];
		if (i == *(char *)key - 'a')
			find_words((void *)((char *)key + 1), next_node, k, found);
		else
			find_words((void *)((char *)key + 1), next_node, k - 1, found);
		
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

	find_words(key, trie->root, k, &found);
	if (!found)
		printf("No words found\n");
}