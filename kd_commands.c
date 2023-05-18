#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kd_tree.h"
#include "kd_commands.h"
#include "kd_aux.h"
#include "aux_functions.h"
#define NMAX 100

void load_cmd(char *command, kd_tree_t **tree)
{
	/*obtinem numele fisierului */
	char *file_name = strtok(command, " ");
	file_name = strtok(NULL, " ");

	FILE *fin = fopen(file_name, "r");
	DIE(!fin, "fopen");

	/* citim nr de puncte si dim lor */
	int n, k;
	fscanf(fin, "%d%d", &n, &k);

	/* cream arborele cu dimensiunea citita anterior*/
	*tree = create_kd_tree(k);
	int *point = malloc(sizeof(int) * k);
	DIE(!point, "malloc");

	/* citim punctele si le inseram in arbore */
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j)
			fscanf(fin, "%d", &point[j]);

		(*tree)->root = insertion(point, (*tree)->root, k, 0);
	}

	/* eliberam memoria */
	free(point);
	fclose(fin);
}

void nn(int *point, kd_node_t *node, int dim, int k, double *best_dist, point_t **neighs, int *size, int *capacity)
{
	if (!node)
		return;

	/* calculam distanta de la punctul dat la nodul curent */
	double dist = distance(point, node->point, k);

	/* daca a este prima distanta gasita, o adaugam in vectorul
	de vecini */
	if (*best_dist == -1) {
		*best_dist = dist;
		add_point(neighs, size, capacity, node->point, dist, k);
	}

	/* daca distanta este mai mica decat cea mai mica distanta gasita,
	stergem elementele din vectorul de vecin,  adaugam noua val 
	si actualizam cea mai mica distanta */
	if (dist < *best_dist) {
		*best_dist = dist;
		purge(neighs, size, capacity);
		add_point(neighs, size, capacity, node->point, dist, k);
	}

	/* daca distanta este egala cu cea mai mica distanta gasita, o adaugam
	in vectorul de vecini */
	if (dist == *best_dist && different_value(*neighs, *size, node->point, k)) {
		add_point(neighs, size, capacity, node->point, dist, k);
	}
	
	if (point[dim] < node->point[dim]) {
		nn(point, node->left, (dim + 1) % k, k, best_dist, neighs, size, capacity);
		nn(point, node->right, (dim + 1) % k, k, best_dist, neighs, size, capacity);
	} else {
		nn(point, node->right, (dim + 1) % k, k, best_dist, neighs, size, capacity);
		nn(point, node->left, (dim + 1) % k, k, best_dist, neighs, size, capacity);
	}
}

void nn_cmd(char *comamnd, kd_tree_t *tree)
{
	char *point_string = strtok(comamnd, " ");
	point_string = strtok(NULL, " ");

	/* alocam punctul */
	int *point = malloc(sizeof(int) * tree->k);
	DIE(!point, "malloc");

	/* citim punctul din stringul dat */
	for (int i = 0; i < tree->k; ++i) {
		point[i] = atoi(point_string);
		point_string = strtok(NULL, " ");
	}

	/* cream un vector care va continue cei mai apropiati
	vecini ai punctului dat */
	int size = 0, capacity = INITAL_SIZE;
	point_t *points = malloc(sizeof(point_t) * capacity);
	DIE(!points, "malloc\n");

	/* cautam cei mai apropiati vecini */
	double best_dist = -1;
	nn(point, tree->root, 0, tree->k, &best_dist, &points, &size, &capacity);

	/* sortam vectorul de vecini */
	qsort(points, size, sizeof(point_t), nn_compare);
	for (int i = 0; i < size; ++i) {
		print_point(points[i].point, tree->k);
		free(points[i].point);
	}

	free(points);
	free(point);
}

void range(kd_node_t *node, int *start, int *end, int dim, int k,
		   point_t **points, int *size, int *capacity)
{
	if (!node)
		return;
	
	/* daca punctul se afla in interval, il adaugam in vectorul de puncte */
	if (check_point(node->point, start, end, k))
		add_point(points, size, capacity, node->point,
				  distance(node->point, start, k), k);

	/* daca valoarea curenta a coordonatei este mai mare decat start,
	cautam in fiul drept */
	if (node->point[dim] >= start[dim])
		range(node->left, start, end, (dim + 1) % k, k, points, size,
			  capacity);

	/* daca valoarea curenta a coordonatei este mai mica decat end, cautam in
	fiul drept */
	if (node->point[dim] <= end[dim])
		range(node->right, start, end, (dim + 1) % k, k, points, size,
			  capacity);

}

void range_cmd(char *command, kd_tree_t *tree)
{
	/* alocam vectorii de start si end */
	int *start = malloc(sizeof(int) * tree->k);
	int *end = malloc(sizeof(int) * tree->k);

	char *point_string = strtok(command, " ");
	point_string = strtok(NULL, " ");

	/* citim punctul de start si punctul de end din stringul primit*/
	for (int i = 0; i < tree->k; ++i) {
		start[i] = atoi(point_string);

		point_string = strtok(NULL, " ");
		end[i] = atoi(point_string);

		point_string = strtok(NULL, " ");
	}

	/* cream vectorul de puncte care se afla in interval */
	int size = 0, capacity = INITAL_SIZE;
	point_t *points = malloc(sizeof(point_t) * capacity);
	DIE(!points, "malloc\n");

	/* cautam punctele din interval */
	range(tree->root, start, end, 0, tree->k, &points, &size, &capacity);

	/* sortam vectorul de puncte dupa distanta de la start*/
	qsort(points, size, sizeof(point_t), range_compare);

	/* afisam punctele */
	for (int i = 0; i < size; ++i) {
		print_point(points[i].point, tree->k);
		free(points[i].point);
	}

	free(points);
	free(start);
	free(end);
}