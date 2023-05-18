#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"
#include "mk_commands.h"

int main(void)
{	
	trie_t *trie = trie_create(sizeof(char) * MAX_WORD_SIZE);
	char *cmd_string;
	int cmd = -1, done = 0;

	while (1) {
		cmd_string = read_cmd();
		mk_commands(&cmd, cmd_string);

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
