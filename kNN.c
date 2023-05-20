#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "math.h"
#include "kd_tree.h"
#include "kd_commands.h"
#include "aux_functions.h"

int main(void)
{
	kd_tree_t *tree = NULL;
	char *cmd_string;
	int cmd = -1, done = 0;

	while (1) {
		cmd_string = read_cmd();
		knn_commands(&cmd, cmd_string);

		switch (cmd) {
		case 1:
			load_cmd(cmd_string, &tree);
			break;
		case 2:
			nn_cmd(cmd_string, tree);
			break;
		case 3:
			range_cmd(cmd_string, tree);
			break;
		case 4:
			free_kd_tree(tree);
			done = 1;
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
