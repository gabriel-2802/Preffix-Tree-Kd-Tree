#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"

/* incarca dintr-un fisier de intrare, punctele din arbore
 * @params1: comanda de la tastatura
 * @params2: arborele k-d
 * */
void load_cmd(char *command, kd_tree_t **tree);

/* gaseste cel mai apropiat vecin de un punct dat
 * @params1: punctul dat
 * @params2: nodul curent
 * @params3: dimensiunea curenta a punctelor
 * @params4: dimensiunea punctelor
 * @params5: cea mai mica distanta gasita
 * @params6: vectorul de vecini
 * @params7: dimensiunea vectorului de vecini
 * @params8: capacitatea vectorului de vecini
 * */
void nn(int *point, kd_node_t *node, int dim, int k, double *best_dist,
		point_t **neighs, int *size, int *capacity);
/* prelucreaza datele de intrare si apeleaza functia nn
 * @params1: comanda
 * @params2: arborele
 */
void nn_cmd(char *comamnd, kd_tree_t *tree);

/* gaseste toti vecinii intr-un anumit range
 * @params1: nodul curent
 * @params2: punctul de inceput al range-ului
 * @params3: punctul de sfarsit al range-ului
 * @params4: dimensiunea curenta a punctelor
 * @params5: dimensiunea punctelor
 * @params6: vectorul de vecini
 * @params7: dimensiunea vectorului de vecini
 * @params8: capacitatea vectorului de vecini
 * */

// alignement should math open paranthesis
void range(kd_node_t *node, int *start, int *end, int dim, int k,
		   point_t **neighs, int *size, int *capacity);
 /* prelucreaza datele de intrare si apeleaza functia range
 * @params1: comanda
 * @params2: arborele
 */
void range_cmd(char *command, kd_tree_t *tree);

