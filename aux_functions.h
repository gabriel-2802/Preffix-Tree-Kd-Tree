#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 100
#define DIE(assertion, call_description) do {				\
	if (assertion) {										\
		fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);	\
		perror(call_description);							\
		exit(errno);										\
	}														\
} while (0)

void mk_commands(int *cmd, char *string);

void knn_commands(int *cmd, char *string);

char *read_cmd(void);

double distance(int *x, int *y, int k);

