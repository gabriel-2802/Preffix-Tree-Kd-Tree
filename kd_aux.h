#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INITAL_SIZE 10

double distance(int *x, int *y, int k);

void add_point(point_t **points, int *size, int *capacity, int *new_point, double dist, int k);

void print_point(int *point, int k);

void purge(point_t **points, int *size, int *capacity);

int different_value(point_t *points, int size, int *new_point, int k);

int nn_compare(const void *a, const void *b);

int range_compare(const void *a, const void *b);

int check_point(int *point, int *start, int *end, int k);