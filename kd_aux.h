#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INITAL_SIZE 10

/* calculeaza distanta euclidiana intre 2 puncte
 *@params1: primul punct
 *@params2: al doilea punct
 *@params3: nr de dimensiuni ale punctelor
 */
double distance(int *x, int *y, int k);

/* se adauga punctul dat la vectorul de puncte
 * @params1: vectorul de puncte
 * @params2: nr de puncte din vector
 * @params3: capacitatea vectorului
 * @params4: punctul de adaugat
 * @params5: distanta de la punctul de start
 * @params6: nr de dimensiuni ale punctelor
 */

void add_point(point_t **points, int *size, int *capacity, int *new_point,
			   double dist, int k);
/* printeaza punctul
 * @params1: punctul
 * @params2: nr de dimensiuni
 */
void print_point(int *point, int k);

/* elibereaza memoria ocupata de vectorul de puncte si realoca vectorul
la dimensiunea initiala
 * @params1: vectorul de puncte
 * @params2: nr de puncte din vector
 * @params3: capacitatea vectorului
 */
void purge(point_t **points, int *size, int *capacity);

/* verifica daca noul punct este deja in vector
 * @params1: vectorul de puncte
 * @params2: nr de puncte din vector
 * @params3: punctul ce verificat
 * @params4: nr de dim*/
int different_value(point_t *points, int size, int *new_point, int k);

/* functie aux pentru qsort, compara 2 puncte dupa coordonate
 * @params1: primul punct
 * @params2: al doilea punct
 */
int nn_compare(const void *a, const void *b);

/* functie aux pentru qsort, compara 2 puncte dupa distanta
pana de la start
 * @params1: primul punct
 * @params2: al doilea punct
 */
int range_compare(const void *a, const void *b);

/* verifica daca punctul se afla in intervalul dat
 * @params1: punctul
 * @params2: punctul de start
 * @params3: punctul de end
 * @params4: nr de dimensiuni
 */
int check_point(int *point, int *start, int *end, int k);
