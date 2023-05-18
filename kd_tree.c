#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "aux_functions.h"
#include "kd_tree.h"

kd_tree_t *create_kd_tree(int k)
{
	kd_tree_t *kd = malloc(sizeof(kd_tree_t));
	DIE(!kd, "malloc");

	kd->k = k;
	kd->root = NULL;

	return kd;
}

kd_node_t *create_kd_node(int *point, int k)
{
	kd_node_t *node = malloc(sizeof(kd_node_t));
	DIE(!node, "malloc");

	node->point = malloc(sizeof(int)* k);
	DIE(!node->point, "malloc");
	memcpy(node->point, point, sizeof(int) * k);

	node->left = NULL;
	node->right = NULL;

	return node;
}

/* https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf */
kd_node_t *insertion(int *point, kd_node_t *node, int k, int dim)
{
	if (!node)
		return create_kd_node(point, k);
	

	if (point[dim] < node->point[dim])
		node->left = insertion(point, node->left, k, (dim + 1) % k);
	else
		node->right = insertion(point, node->right, k, (dim + 1) % k);
	
	return node;
}

void free_kd_node(kd_node_t *node)
{
	if (!node)
		return;

	free_kd_node(node->left);
	free_kd_node(node->right);
	free(node->point);
	free(node);
}


void free_kd_tree(kd_tree_t *tree)
{
	if (!tree)
		return;

	free_kd_node(tree->root);
	free(tree);
}