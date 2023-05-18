#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

void load_cmd(char *command, kd_tree_t **tree);

void nn(int *point, kd_node_t *node, int dim, int k, double *best_dist, point_t **neighs, int *size, int *capacity);

void nn_cmd(char *comamnd, kd_tree_t *tree);

void range(kd_node_t *node, int *start, int *end, int dim, int k, point_t **points, int *size, int *capacity);

void range_cmd(char *command, kd_tree_t *tree);


