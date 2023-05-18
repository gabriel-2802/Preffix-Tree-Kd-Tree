#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

typedef struct kd_node_t kd_node_t;
typedef struct kd_tree_t kd_tree_t;
typedef struct point point_t;

struct kd_node_t {
	int *point;
	kd_node_t *left, *right;
};

struct kd_tree_t {
	int k;
	kd_node_t *root;

};

struct point {
	int *point;
	double dist_from_start;
};

kd_tree_t *create_kd_tree(int k);

kd_node_t *create_kd_node(int *point, int k);

kd_node_t *insertion(int *point, kd_node_t *node, int k, int dim);

void free_kd_node(kd_node_t *node);

void free_kd_tree(kd_tree_t *tree);