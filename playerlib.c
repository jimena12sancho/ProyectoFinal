#include "playerlib.h"
bool change_player(bool * current_player){
    *current_player = !(*current_player);
    return *current_player;
}

struct player init_player(){
    struct player temp;
    temp.cant_fusions = 0;
    memset(&temp.hand, 0, sizeof(int));
    assert(!init(&temp.hand, sizeof(struct pcard)));
    temp.main_table = malloc(15 * sizeof(vec_t));
    for (int i = 0; i < 12; ++i)
        temp.main_table[i] = init_deck(0, 0);
    return temp;
}
