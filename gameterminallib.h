//
// Created by br14n on 7/12/22.
//

#ifndef SHARLIN_GAMETERMINALLIB_H
#define SHARLIN_GAMETERMINALLIB_H
#include "vec.h"
#include "utilsfun.h"
#include "pcardlib.h"
#include "playerlib.h"
void cstatus_game_terminal(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd);
void card_to_discard_game(struct player* p, vec_t deck, vec_t* stack_deck, struct pcard* top_stackd);
void card_fusion_game(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd, int current_player);
int knock_alert_game(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd, bool *current_player, bool* SOMEONEWONTWIN);
void saved_score_game(char path[], char name[], int score);
void show_best_score_game(char path[]);
#endif //SHARLIN_GAMETERMINALLIB_H
