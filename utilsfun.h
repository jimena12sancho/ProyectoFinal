#ifndef SHARLIN_UTILSFUN_H
#define SHARLIN_UTILSFUN_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "vec.h"
#include "pcardlib.h"
int compare_score(void * score1, void * score2);
bool inRange(int low, int high, int n);
void swap (void* a, void* b);

void pushback_deck(void * deck, struct pcard _pcrd);
vec_t init_deck(int NTYPES, int NCARDS);
void show_deck(vec_t deck);
struct pcard getpcard_deck(vec_t deck, int index);
void shuffle_deck(vec_t* deck);
bool search_in_deck(vec_t deck, struct pcard cardtofind);
bool testing_deck(vec_t deck);
struct pcard popback_deck(void * deck);
struct pcard at_deck(void* deck, int index, struct pcard p);
int analysis_sub_deck(vec_t *deck);
bool is_knock_deck(vec_t deck);
int sum_current_deck(vec_t deck);

#endif //SHARLIN_UTILSFUN_H
