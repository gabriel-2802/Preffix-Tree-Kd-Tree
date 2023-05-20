#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

typedef struct kd_node_t kd_node_t;
typedef struct kd_tree_t kd_tree_t;
typedef struct point point_t;

/* nodul de kd-tree va continue un vector 'punctul'
si pointeri catre fii*/
struct kd_node_t {
	int *point;
	kd_node_t *left, *right;
};

/* structura de kd-tree va contine numarul de dimensiuni
si radacina */
struct kd_tree_t {
	int k;
	kd_node_t *root;

};

/* structura auxiliara, folosita in sortare */
struct point {
	int *point;
	double dist_from_start;
};

/* creeaza arborele
 * @params1: nr de dimensiuni
 */
kd_tree_t *create_kd_tree(int k);

/* creeaza un nod
 * @params1: punctul
 * @params2: nr de dimensiuni
 */
kd_node_t *create_kd_node(int *point, int k);

/* insereaza un nod in arbore
 * @params1: punctul
 * @params2: nodul curent
 * @params3: nr de dimensiuni
 * @params4: dimensiunea curenta
 */
kd_node_t *insertion(int *point, kd_node_t *node, int k, int dim);

/* elibereaza subarborii si nodul primit ca arg
 * @params1: nodul
 */
void free_kd_node(kd_node_t *node);

/* elibereaza arborele si nodurile sale
 * @params1: arborele
 */
void free_kd_tree(kd_tree_t *tree);
