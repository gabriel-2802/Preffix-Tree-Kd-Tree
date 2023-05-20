#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"

/* prelucreaza comanda primita si apeleaza insert
 * @params1: comanda
 * @params2: arborele
 */
void insert_cmd(char *command, trie_t *trie);

/* prelucreaza comanda primita si apeleaza load
 * @params1: comanda
 * @params2: arborele
 */
void load_cmd(char *command, trie_t *trie);

/* prelucreaza comanda primita si apeleaza remove
 * @params1: comanda
 * @params2: arborele
 */
void remove_cmd(char *command, trie_t *trie);

/* prelucreaza comanda primita si apeleaza search pt a
gasi cuvantul cautat
 * @params1: comanda
 * @params2: arborele
 */
void find_cmd(char *command, trie_t *trie);

/* cauta cuvinte care au maxim k litere diferite fata de
cheia data
 * @params1: cheia (cuvantul
 * @params2: nodul din arbore
 * @params3: nr de litere diferite permise
 * @params4: variabila 'bool', care marcheaza daca este gasit un cuvant
 */
void find_words(void *key, tnode_t *root, int k, int *found);

/* prelucreaza comanda primita, ontine cheia si k, si apeleaza find_words
 * @params1: comanda
 * @params2: arborele
 */
void autocorrect_cmd(char *command, trie_t *trie);

/* cauta cel mai mic cuvant lexicografic, pornind de la un nod
 * @params1: nodul din arbore
 * @params2: arborele
 * @return: nodul cu cel mai mic cuvant
 */
tnode_t *find_first_word(tnode_t *root);

/* afiseaza cel mai mic cuvant lexicografic, pornind de la un nod,
apelad functia find_first_word
 * @params1: nodul din arbore
 */
void print_first_word(tnode_t *pref_node);

/* cauta cel scurt cuvant, pornind de la un nod
 * @params1: nodul cu pref dat
 * @params2: cuvantul celi mai scurt
 * @params3: lungimea minima a cuvantului
 */
void find_shortest_word(tnode_t *pref_node, char *word, int *min_size);

/*printeaza cel mai scurt cuvant, pornind de la un nod, apeland
functia find_shprtest_word
 *@params1: nodul cu prefixul dat*/
void print_shortest_word(tnode_t *pref_node);

/* cauata cel mai frecvent cuvant din arbore
 * @params1: nodul cu pref dat
 * @params2: cuvantul cel mai frecvent
 * @params3: frecventa cuvantului
 */
void find_most_freq_word(tnode_t *pref_node, char *word, int *freq);

/*printeaza cel mai frecvent cuvant, pornind de la un nod, apeland
functia find_most_freq_word
 *@params1: nodul cu prefixul dat*/
void print_most_freq_word(tnode_t *pref_node);

/* prelucreaza comanda primita si apeleaza functiile de find
dupa criteriul extras din comanda
 * @params1: comanda
 * @params2: arborele
 */
void autocomplete_cmd(char *command, trie_t *trie);
