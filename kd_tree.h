#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"
#define DIE(assertion, call_description) do {				\
	if (assertion) {										\
		fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);	\
		perror(call_description);							\
		exit(errno);										\
	}														\
} while (0)

typedef struct kd_node_t kd_node_t;
typedef struct kd_tree_t kd_tree_t;

struct kd_node_t {
	void *point;
	kd_node_t *left, *right;
};

struct kd_tree_t {
	int k;
	int data_size;
	kd_node_t *root;

};

kd_tree_t *create_kd(int k, int data_size);

kd_node_t *create_kd_node(void *point, int data_size, int k);

kd_node_t *insertion(void *point, kd_node_t *node, int data_size, int k, int dim);

void free_kd_node(kd_node_t *node);

void free_kd_tree(kd_tree_t *tree);