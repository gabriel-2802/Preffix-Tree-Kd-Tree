#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

kd_tree_t *create_kd(int k, int data_size)
{
	kd_tree_t *kd = malloc(sizeof(kd_tree_t));
	DIE(!kd, "malloc");

	kd->k = k;
	kd->data_size = data_size;
	kd->root = NULL;

	return kd;
}

kd_node_t *create_kd_node(void *point, int data_size, int k)
{
	kd_node_t *node = malloc(sizeof(kd_node_t));
	DIE(!node, "malloc");

	node->point = malloc(data_size * k);
	DIE(!node->point, "malloc");
	memcpy(node->point, point, data_size * k);

	node->left = NULL;
	node->right = NULL;

	return node;
}


kd_node_t *insertion(void *point, kd_node_t *node, int data_size, int k, int dim)
{
	if (!node)
		return create_kd_node(point, data_size, k);
	
	int cmp_res = memcmp((char *)point + dim * data_size, (char *)node->point + dim * data_size, data_size);

	if (cmp_res < 0)
		node->left = insertion(point, node->left, data_size, k, (dim + 1) % k);
	else
		node->right = insertion(point, node->right, data_size, k, (dim + 1) % k);
	
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