#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"
#define NMAX 100

void command(int *cmd, char *string)
{
	/*pentru un meniu mai eye-candy vom transforma comanda primita
	in valori numerice */
	char copy[NMAX];
	//folosim a copie pentru a nu denatura string-ul cu strtok
	strcpy(copy, string);
	char *first_word = strtok(copy, " ");

	if (!strcmp(first_word, "LOAD"))
		*cmd = 1;
	else if (!strcmp(first_word, "NN"))
		*cmd = 2;
	else if (!strcmp(first_word, "RANGE"))
		*cmd = 3;
	else if (!strcmp(string, "EXIT"))
		*cmd = 4;
	else
		*cmd = -1;
}

char *read_cmd(void)
{
	//citim comanda primita
	char command[NMAX];
	fgets(command, NMAX - 1, stdin);

	//eliminam \n de la finalul string ului citit
	int len = strlen(command);
	if (command[len - 1] == '\n') {
		command[len - 1] = '\0';
		len--;
	}
	//crestem len pentru a copia si \0
	len++;

	char *cmd = malloc(len * sizeof(char));
	if (!cmd)
		return NULL;

	strcpy(cmd, command);
	return cmd;
}

void load_cmd(char *command, kd_tree_t *tree)
{
	char *file_name = strtok(command, " ");
	file_name = strtok(NULL, " ");

	FILE *fin = fopen(file_name, "r");
	DIE(!fin, "fopen");

	int n, k;
	fscanf(fin, "%d%d", &n, &k);

	int *point = malloc(sizeof(int) * k);
	DIE(!point, "malloc");

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j)
			fscanf(fin, "%d", &point[j]);

		tree->root = insertion(point, tree->root, sizeof(int), k, 0);
	}

	free(point);
	fclose(fin);
}