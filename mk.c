#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"
#include "mk_commands.h"


tnode_t search_prefix(char *key, trie_t *trie)
{
	
}


void smallest_word(char *key, trie_t *trie)
{	

}

void shortest_word();

void most_freq_word();

void autocomplete_cmd(char *command, trie_t *trie)
{
	char *key, *criterium;
	key = strtok(command, " ");
	key = strtok(NULL, " ");
	criterium = strtok(NULL, " ");
	int crit = atoi(criterium);

	switch (crit) {
		case 1:
			smallest_word(key, trie);
			break;
		case 2:
			shortest_word(key, trie);
			break;
		case 3:	
			most_freq_word(key, trie);
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
			//AUTOCOMPLETE
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
