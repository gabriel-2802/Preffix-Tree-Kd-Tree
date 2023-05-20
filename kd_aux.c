#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kd_tree.h"
#include "kd_aux.h"
#include "kd_commands.h"
#include "aux_functions.h"

double distance(int *x, int *y, int k)
{
	double dist = 0, xi, yi;

	/* se parcurg toate coordonatele celor 2 puncte */
	for (int i = 0; i < k; ++i) {
		xi = (double)x[i];
		yi = (double)y[i];

		dist += (yi - xi) * (yi - xi);
	}

	return sqrt(dist);
}

void add_point(point_t **points, int *size, int *capacity,
			   int *new_point, double dist, int k)
{
	/* daca nr de elemente este egal cu val maxima a array-ului
	vom dubla capacitatea si realocam intreg vectorul */
	if (*size == *capacity) {
		*capacity *= 2;
		/* programare defensiva */
		point_t *aux = realloc(*points, sizeof(point_t) * (*capacity));
		DIE(!aux, "realloc");

		*points = aux;
	}

	/* alocam noul punct */
	(*points)[*size].point = malloc(sizeof(int) * k);
	DIE(!(*points)[*size].point, "malloc");

	/* adaugam noul punct in vector */
	memcpy((*points)[*size].point, new_point, sizeof(int) * k);
	(*points)[*size].dist_from_start = dist;
	(*size)++;
}

void print_point(int *point, int k)
{
	for (int i = 0; i < k; ++i)
		printf("%d ", point[i]);
	printf("\n");
}

void purge(point_t **points, int *size, int *capacity)
{
	/* eliberam intreg vectorul de puncte din memorie */
	for (int i = 0; i < *size; ++i)
		free((*points)[i].point);
	*size = 0;

	/* realocam vectorul la valorea initala, minima */
	*capacity = INITAL_SIZE;
	point_t *aux = realloc(*points, sizeof(point_t) * (*capacity));
	DIE(!(*points), "malloc");
	*points = aux;
}

int different_value(point_t *points, int size, int *new_point, int k)
{
	/* verificam daca noul punct este deja in vector */
	for (int i = 0; i < size; ++i)
		if (!memcmp(points[i].point, new_point, sizeof(int) * k))
			return 0;

	return 1;
}

int nn_compare(const void *a, const void *b)
{
	/* comparam punctele coordonata cu coordonata */
	return !memcmp(a, b, sizeof(point_t));
}

int range_compare(const void *a, const void *b)
{
	/* comparam distantele de la punctul de start */
	double x = ((point_t *)a)->dist_from_start;
	double y = ((point_t *)b)->dist_from_start;

	if (x >= y)
		return 1;

	return -1;
}

int check_point(int *point, int *start, int *end, int k)
{
	/* verificam daca punctul se afla in intervalul dat */
	for (int i = 0; i < k; ++i)
		if (point[i] < start[i] || point[i] > end[i])
			return 0;
	return 1;
}

