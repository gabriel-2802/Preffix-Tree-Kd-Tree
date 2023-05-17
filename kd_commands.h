#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

void command(int *cmd, char *string);

char *read_cmd(void);

void load_cmd(char *command, kd_tree_t *tree);

