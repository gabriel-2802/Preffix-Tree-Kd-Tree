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

	for (int i = 0; i < k ;++i) {
		xi = (double)x[i];
		yi = (double)y[i];

		dist += (yi - xi) * (yi - xi);
	}

	return sqrt(dist);
}

void add_point(point_t **points, int *size, int *capacity, int *new_point, double dist, int k)
{
	if (*size == *capacity) {
		*capacity *= 2;
		point_t *aux = realloc(*points, sizeof(point_t) * (*capacity));
		DIE(!aux, "realloc");

		*points = aux;
	}

	(*points)[*size].point = malloc(sizeof(int) * k);
	DIE(!(*points)[*size].point, "malloc");

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

void purge (point_t **points, int *size, int *capacity)
{
	for (int i = 0; i < *size; ++i)
		free((*points)[i].point);
	free(*points);
	*size = 0;

	*capacity = INITAL_SIZE;
	*points = malloc(sizeof(point_t) * (*capacity));
	DIE(!(*points), "malloc");
}


int different_value(point_t *points, int size, int *new_point, int k)
{
	for (int i = 0; i < size; ++i)
		if (!memcmp(points[i].point, new_point, sizeof(int) * k))
			return 0;
		
	return 1;
}

int nn_compare(const void *a, const void *b)
{
	return !memcmp(a, b, sizeof(point_t));
}

int range_compare(const void *a, const void *b)
{
	double x = ((point_t *)a)->dist_from_start;
	double y = ((point_t *)b)->dist_from_start;

	if (x >= y)
		return 1;

	return -1;
}


int check_point(int *point, int *start, int *end, int k)
{
	for (int i = 0; i < k; ++i)
		if (point[i] < start[i] || point[i] > end[i])
			return 0;
	return 1;
}

