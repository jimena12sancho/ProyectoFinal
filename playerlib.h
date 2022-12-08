#ifndef SHARLIN_PLAYERLIB_H
#define SHARLIN_PLAYERLIB_H
#include "vec.h"
#include "pcardlib.h"
struct player{
    char *name;
    vec_t hand;
    vec_t *main_table;
    int cant_fusions;
};

bool change_player(bool * current_player);
struct player init_player();
#endif //SHARLIN_PLAYERLIB_H
