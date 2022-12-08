//
// Created by br14n on 4/12/22.
//
#include "utilsfun.h"

int compare_score(void * score1, void * score2){
    int lr = *((int*)score1);
    int ll = *((int*)score2);
    return (ll - lr);
}
bool inRange(int low, int high, int n){
    return (n - high) * (n - low) <= 0;
}

void swap (void* a, void* b){
    void * tmp = (malloc(sizeof(void *)));
    memcpy(tmp, a, sizeof (void *));
    memcpy(a, b, sizeof (void *));
    memcpy(b, tmp, sizeof (void *));
}

void pushback_deck(void * deck, struct pcard _pcrd){
    assert(!append(((vec_t *) deck), &_pcrd));
}


vec_t init_deck(int NTYPES, int NCARDS){
    char T[4] = {'P', 'C', 'D', 'T'};
    vec_t instance_deck;
    memset(&instance_deck, 0, sizeof(int));
    assert(!init(&instance_deck, sizeof(struct pcard)));
    for (int type = 0; type < NTYPES; ++type)
        for (int card = 1; card <= NCARDS; ++card)
            //struct pcard current_card = _pcard(T[type], card);
            //assert(!append(&instance_deck, &current_card));
            pushback_deck(&instance_deck, _pcard(T[type], card));
    return instance_deck;
}

void show_deck(vec_t deck){
    struct pcard t;
    for (int i = 0; i < deck.size; ++i){
        get(&deck, i, &t);
        printf("{%c, %d}\n", t.type, t.number);
    }
}

struct pcard getpcard_deck(vec_t deck, int index){
    struct pcard temp;
    get(&deck, index, &temp);
    return temp;
}

void shuffle_deck(vec_t* deck){
    for(int i = 0; i < (*deck).size; ++i){
        int random_index = i + (rand() % ((*deck).size - i));
        struct pcard pi = getpcard_deck((*deck), i);
        struct pcard pr = getpcard_deck((*deck), random_index);
        //printf("pi:{%c %d} <-> pr:{%c %d} (i: %d)\n", pi.type, pi.number, pr.type, pr.number, i);
        replace(deck, &pi, random_index);
        replace(deck, &pr, i);
    }
}

bool search_in_deck(vec_t deck, struct pcard cardtofind){
    for(int i = 0; i < deck.size; ++i){
        struct pcard card_i = getpcard_deck(deck, i);
        if ((card_i.number == cardtofind.number) && (card_i.type == cardtofind.type))
            return true;
    }
    return false;
}

bool testing_deck(vec_t deck){
    for (int i = 0; i < deck.size; ++i){
        int cont  = 0;
        struct pcard temp = getpcard_deck(deck, i);
        for (int j = 0; j < deck.size; ++j) {
            struct pcard current_j  = getpcard_deck(deck, j);
            if ((current_j.number == temp.number) && (current_j.type == temp.type)) cont ++;
        }
        if ((cont == 0) ||  cont > 1)//{
            //printf("testing failed: ");
            return false;
        // }
        // printf("temp: {%c %d} -> %d\n", temp.type, temp.number, cont);
    }
    return true;
}


struct pcard popback_deck(void * deck){
    struct pcard empty;
    if(((vec_t*)deck)->size == 0)
        return empty;
    struct pcard tempfine = getpcard_deck(*((vec_t*)deck), ((vec_t*)deck)->size - 1);
    remove_index(((vec_t*)deck), ((vec_t*)deck)->size - 1);
    return tempfine;
}

struct pcard at_deck(void* deck, int index, struct pcard p){
    struct pcard temp = p;
    replace(((vec_t *) deck), &p, index);
}

int analysis_sub_deck(vec_t *deck){
    bool STAIRS = true;
    bool TRIA = true;
    sort(deck, (cmpfn) pcard_comparator);

    if ((*deck).size < 3) return 0;

    for(int i = 0; i < (*deck).size - 1; ++i){
        struct pcard cardi = getpcard_deck((*deck), i);
        struct pcard cardiplus = getpcard_deck((*deck), i + 1);
        if((cardiplus.number - cardi.number != 1) && (cardiplus.type != cardi.type))
            STAIRS = false;
    }

    struct pcard cardi = getpcard_deck((*deck), 0);
    for(int i = 1; i < (*deck).size; ++i){
        struct pcard cardiplus = getpcard_deck((*deck), i);
        if (cardi.number != cardiplus.number)
            TRIA = false;
    }
    if(STAIRS) return 2;
    else if (TRIA) return 1;
    else return 0;
}

bool is_knock_deck(vec_t deck){
    int MAXKNOCK = 10,
            count = 0;
    for (int i = 0; i < deck.size; ++i){
        struct pcard card = getpcard_deck(deck, i);
        count += card.number;
        if (count > MAXKNOCK)
            return  false;
    }

    return true;
}

int sum_current_deck(vec_t deck){
    int MAXKNOCK = 10,
            count = 0;
    for (int i = 0; i < deck.size; ++i){
        struct pcard card = getpcard_deck(deck, i);
        count += card.number;
    }

    return count;
}