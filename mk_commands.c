#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"
#include "aux_functions.h"

void insert_cmd(char *command, trie_t *trie)
{
	/* obtinem cuvantul*/
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	/* il inseram in arbore */
	insert_trie(trie, key);
}

void load_cmd(char *command, trie_t *trie)
{
	/* obtinem numele fisierlui */
	char *file_name;
	file_name = strtok(command, " ");
	file_name = strtok(NULL, " ");

	FILE *fin = fopen(file_name, "r");
	DIE(!fin, "fopen");

	char *line = NULL;
	size_t buff_len = 0;

	/* nestiind lungimea maxima a unei linii din fisier, utilizam
	getline, care citeste intreaga linie si aloca dinamic memoria pentru
	aceasta */
	while (getline(&line, &buff_len, fin) != -1) {
		int len = strlen(line);
		/* eliminam caracterul '\n' de la finalul liniei */
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';

		len = strlen(line);
		/* eliminam caracterele care nu sunt litere mici */
		for (int i = 0; i < len; ++i)
			if ((line[i] < 'a' || line[i] > 'z'))
				line[i] = ' ';

		/* obtinem cuvintele din linie si le inseram in arbore */
		char *key = strtok(line, " \t");
		while (key) {
			insert_trie(trie, key);
			key = strtok(NULL, " ");
		}
	}
	/* eliberam memoria si inchidem fisierul */
	fclose(fin);
	free(line);
}

void remove_cmd(char *command, trie_t *trie)
{
	/* obtinem cuvantul */
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	/* il eliminam din arbore */
	remove_value(trie->root, key);
}

void find_cmd(char *command, trie_t *trie)
{
	/* obtinem cuvantul */
	char *key;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	/* cautam cuvantul in arbore */
	tnode_t *node = search(key, trie->root, trie->data_size);
	if (node)
		printf("%s %d\n", (char *)node->value, node->freq);
	else
		printf("No result\n");
}

void find_words(void *key, tnode_t *root, int k, int *found, int size)
{
	/* daca nodul nu exista sau nr de modificari permise e negativ, dam
	return */
	if (!root || k < 0)
		return;

	/* daca cuvantul are mai multe litere decat cuvantul pe care il
	corectam, dam return */
	if (root->value)
		if ((int)strlen((char *)root->value) > size)
			return;

	/* daca am gasit un cuvant, il afisam */
	if (*(char *)key == '\0' && root->end_word == 1)  {
		printf("%s\n", (char *)root->value);
		/* daca am gasit un cuvant, found devine 1 */
		*found = 1;
		return;
	}

	/* cautam alte posibile cuvinte in copiii nodului */
	tnode_t *next_node;
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		next_node = root->children[i];
		/* daca litera fiului este identica cu prima litera a cheii, nr de
		caractere modificabile ramane constant */
		if (i == *(char *)key - 'a')
			find_words((void *)((char *)key + 1), next_node, k, found, size);
		else
			/* daca litera fiului este diferita de prima litera a cheii, nr de
			caractere modificabile scade cu 1 */
			find_words((void *)((char *)key + 1), next_node, k - 1,
					   found, size);
	}
}

void autocorrect_cmd(char *command, trie_t *trie)
{
	/* obtinem cuvantul si nr de modificari permise */
	int found = 0;
	char *key, *kk;

	key = strtok(command, " ");
	key = strtok(NULL, " ");

	kk = strtok(NULL, " ");
	int k = atoi(kk);

	find_words(key, trie->root, k, &found, (int)strlen(key));
	/* daca nu am gasit niciun cuvant (found = 0),
		afisam mesajul de eroare */
	if (!found)
		printf("No words found\n");
}

tnode_t *find_first_word(tnode_t *root)
{
	if (!root)
		return NULL;

	/* daca nodul este sfarsit de cuvant, am gasit cuvantul */
	if (root->end_word)
		return root;

	/* cautam primul cuvant in primul fiu al nodului */
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		tnode_t *next_node = root->children[i];
		if (next_node)
			return find_first_word(next_node);
	}

	return NULL;
}

void print_first_word(tnode_t *pref_node)
{
	/* daca prefixul primit este sfarsit de cuvant, printam
	cuvantul */
	if (pref_node->end_word) {
		printf("%s\n", (char *)pref_node->value);
		return;
	}

	/* altfel, cautam primul cuvant */
	tnode_t *print_first_word = find_first_word(pref_node);
	printf("%s\n", (char *)print_first_word->value);
}

void find_shortest_word(tnode_t *pref_node, char *word, int *min_size)
{
	/* daca nodul este sfarsit de cuvant si lungimea cuvantului este mai
	mica decat lungimea minima, actualizam lungimea minima si cuvantul */
	if (pref_node->end_word && (int)strlen((char *)pref_node->value) <
		*min_size) {
		*min_size = strlen((char *)pref_node->value);
		strcpy(word, (char *)pref_node->value);
	}

	/* cautam cuvantul in toti copiii nodului */
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		tnode_t *next_node = pref_node->children[i];
		if (next_node)
			find_shortest_word(next_node, word, min_size);
	}
}

void print_shortest_word(tnode_t *pref_node)
{
	/* alocam memorie pentru cuvant */
	char *word = malloc(MAX_WORD_SIZE);
	DIE(!word, "malloc word");

	/* initializam lungimea minima cu lungimea maxima */
	int min_size = MAX_WORD_SIZE;
	find_shortest_word(pref_node, word, &min_size);

	/* daca lungimea minima este egala cu lungimea maxima, nu am gasit
	niciun cuvant */
	if (min_size == MAX_WORD_SIZE)
		printf("No words found\n");
	else
		printf("%s\n", word);
	free(word);
}

void find_most_freq_word(tnode_t *pref_node, char *word, int *freq)
{
	/* daca nodul este sfarsit de cuvant si frecventa cuvantului este mai
	mare decat frecventa maxima, actualizam frecventa maxima si cuvantul */
	if (pref_node->end_word && pref_node->freq > *freq) {
		*freq = pref_node->freq;
		strcpy(word, (char *)pref_node->value);
	}

	/* cautam cuvantul in toti copiii nodului */
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		tnode_t *next_node = pref_node->children[i];
		if (next_node)
			find_most_freq_word(next_node, word, freq);
	}
}

void print_most_freq_word(tnode_t *pref_node)
{
	char *word = malloc(MAX_WORD_SIZE);
	DIE(!word, "malloc word");
	/* initializam frecventa maxima cu -1 */
	int freq = -1;

	find_most_freq_word(pref_node, word, &freq);
	/* daca frecventa maxima este egala cu -1, nu am gasit niciun
	cuvant */
	if (freq != -1)
		printf("%s\n", word);
	else
		printf("No words found\n");

	free(word);
}

void autocomplete_cmd(char *command, trie_t *trie)
{
	/* obtinem prefixul si criteriul */
	char *key, *criterium;
	key = strtok(command, " ");
	key = strtok(NULL, " ");

	criterium = strtok(NULL, " ");
	int crit = atoi(criterium);

	/* cautam prefixul in trie */
	tnode_t *pref_node = search_prefix(key, trie->root);
	/* daca nu am gasit prefixul, afisam mesajul de eroare */
	if (!pref_node) {
		printf("No words found\n");

		if (!crit) {
			printf("No words found\n");
			printf("No words found\n");
		}
		return;
	}

	/* in functie de criteriu, afisam cuvantul cautat */
	switch (crit) {
	case 0:
		print_first_word(pref_node);
		print_shortest_word(pref_node);
		print_most_freq_word(pref_node);
		break;
	case 1:
		print_first_word(pref_node);
		break;
	case 2:
		print_shortest_word(pref_node);
		break;
	case 3:
		print_most_freq_word(pref_node);
		break;
	}
}
