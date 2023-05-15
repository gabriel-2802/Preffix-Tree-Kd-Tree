#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux_functions.h"

void command(int *cmd, char *string)
{
	/*pentru un meniu mai eye-candy vom transforma comanda primita
	in valori numerice */
	char copy[NMAX];
	//folosim a copie pentru a nu denatura string-ul cu strtok
	strcpy(copy, string);
	char *first_word = strtok(copy, " ");

	if (!strcmp(first_word, "INSERT"))
		*cmd = 1;
	else if (!strcmp(first_word, "LOAD"))
		*cmd = 2;
	else if (!strcmp(first_word, "REMOVE"))
		*cmd = 3;
	else if (!strcmp(first_word, "AUTOCORRECT"))
		*cmd = 4;
	else if (!strcmp(first_word, "AUTOCOMPLETE"))
		*cmd = 5;
	else if (!strcmp(string, "EXIT"))
		*cmd = 6;
    else if (!strcmp(first_word, "FIND"))
        *cmd = 7;
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