#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "math.h"
#include "kd_tree.h"
#include "kd_commands.h"

double distance(void *x, void *y, int k, int data_size)
{
	double dist = 0, xi, yi;

	for (int i = 0; i < k ;++i) {
		xi = (double) *((char *)x + i * data_size);
		yi = (double) *((char *)y + i * data_size);

		dist += (yi - xi) * (yi - xi);
	}

	return sqrt(dist);
}

void nn_command(char *comamnd, kd_tree_t *tree)
{
	char *point_string = strtok(comamnd, " ");
	point_string = strtok(NULL, " ");

	void *point = malloc(tree->data_size * tree->k);
	DIE(!point, "malloc");

}

int main(void)
{

	kd_tree_t *tree = create_kd(3, sizeof(int));
	char *cmd_string;
	int cmd = -1, done = 0;

	while (1) {
		cmd_string = read_cmd();
		command(&cmd, cmd_string);

		switch (cmd) {
		case 1:
			load_cmd(cmd_string, tree);
			break;	
		case 2:
			// NN_cmd(cmd_string, tree);
			break;
		case 3:
		// range_cmd(cmd_string, tree);
			break;
		case 4:
			free_kd_tree(tree);
			done = 1;
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
