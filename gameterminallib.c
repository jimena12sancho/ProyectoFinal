#include "gameterminallib.h"
void cstatus_game_terminal(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd){
    printf("\n\n[Cartas de %s]: ", players[0].name);
    struct pcard t;
    for (int i = 0; i < players[0].hand.size; ++i){
        get(&players[0].hand, i, &t);
        printf("[%d]{%c, %d} ", i, t.type, t.number);
    }

    printf("\n\n\n\n\n\t\t\t\t [Mazo principal: {%d}][Tope de mazo de descarte : {%c, %d}]"
           "\t\t\t\t\t"
           "\n\n\n\n\n", deck.size, top_stackd.type, top_stackd.number);

    printf("[Cartas de %s]: ", players[1].name);
    struct pcard z;
    for (int i = 0; i < players[1].hand.size; ++i){
        get(&players[1].hand, i, &z);
        printf("[%d]{%c, %d} ", i, z.type, z.number);
    }
}

void card_to_discard_game(struct player* p, vec_t deck, vec_t* stack_deck, struct pcard* top_stackd){
    int tempindexcard = -1;
    bool CORRECTSELECTION = true;
    do{
        printf("\n\n %s, Descarte 1 carta de su mano seleccionando su indice: ", p->name);
        scanf("%d", &tempindexcard);
        if(inRange(0, p->hand.size - 1, tempindexcard)){
            struct pcard card_to_discard = getpcard_deck(p->hand, tempindexcard);
            if(tempindexcard == p->hand.size - 1){
                printf("%s, No puedes descartar un carta recientemente seleccionada \n", p->name);
                continue;
            }
            remove_index(&p->hand, tempindexcard);
            pushback_deck(stack_deck, card_to_discard);
            *top_stackd = getpcard_deck((*stack_deck), (*stack_deck).size - 1);
            CORRECTSELECTION = false;
        }
    } while (CORRECTSELECTION);
}

void card_fusion_game(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd, int current_player){
    int REPLY = 1;
    int fusion_index = 0;

    do{
        vec_t subdeck = init_deck(0, 0);
        cstatus_game_terminal(players, deck, stack_deck, top_stackd);
        printf("\n%s, Quieres Fusionar? 1/0: ", players[current_player].name); scanf("%d", &REPLY);
        if (!REPLY) break;
        printf("\n%s, Entra los indices de las cartas seguidos de espacio a fucionar\n"
               "(Detalles -999 para terminar la lectura)"
               "Indices fuera de rango se toman como final de lectura :)\n"
               "Indices a fucionar: ", players[current_player].name);
        while(scanf("%d",&fusion_index) != EOF && (fusion_index != -999)
              && inRange(0, players[current_player].hand.size -1, fusion_index))
            pushback_deck(&subdeck,
                          getpcard_deck(players[current_player].hand,
                                        fusion_index
                          ));
        int RESULT = analysis_sub_deck(&subdeck);
        if (RESULT == 2){
            printf("Hay una escalera en su seleccion\n");
            show_deck(subdeck);
            int cp_size =  players[current_player].main_table->size;

            for (int i = 0; i < subdeck.size; ++i){
                struct pcard target = getpcard_deck(subdeck, i);
                pushback_deck(&players[current_player].main_table[cp_size], target);
                remove_element(&players[current_player].hand, &target);
            }
            printf("Escalera guardada en mazo secundario \n");
            players[current_player].main_table->size += 1;

        }
        else if (RESULT == 1){
            printf("Hay una tria\n");
            show_deck(subdeck);
            int cp_size =  players[current_player].main_table->size;
            for (int i = 0; i < subdeck.size; ++i){
                struct pcard target = getpcard_deck(subdeck, i);
                pushback_deck(&players[current_player].main_table[cp_size], target);
                remove_element(&players[current_player].hand, &target);
            }
            printf("Tria guardada en mazo secundario \n");
            players[current_player].main_table->size += 1;
        }
        else printf("Su fusion no cumple ningun requisito\n");

        show_deck(subdeck);

    }while(true);
}

int knock_alert_game(struct player players[], vec_t deck, vec_t stack_deck, struct pcard top_stackd, bool *current_player, bool* SOMEONEWONTWIN){
    bool ISKNOCK = is_knock_deck(players[*current_player].hand);
    if (ISKNOCK){
        printf("Anunciaste Knock!\n");
        int sumcurrentplayer = sum_current_deck(players[*current_player].hand),
                sumrivalplayer = sum_current_deck(players[!(*current_player)].hand);

        printf("%s, Tu puntuacion para las nos emparejadas es: %d", players[*current_player].name, sumcurrentplayer);
        *current_player = !(*current_player);
        printf("%s, Aprovecha para deshacer las cartas no emparejadas \n", players[*current_player].name);
        card_fusion_game(players, deck, stack_deck, top_stackd, (int) *(current_player));

        bool final_annotations = sum_current_deck(players[!(*current_player)].hand) < sum_current_deck(players[*current_player].hand);
        printf("%s",((final_annotations) ? "Ganaste la Ronda" : "Perdiste la Ronda"));
        if(final_annotations){
            *current_player = !(*current_player);
            printf("Tu Puntuacion final es de: %d pts", sumcurrentplayer + sumrivalplayer);

        }
        *SOMEONEWONTWIN = true;
        return (sumcurrentplayer + sumrivalplayer);
    }
    return -9999;
}

void saved_score_game(char path[], char name[], int score){
    FILE *fptr;
    fptr = fopen(path, "a");

    assert(fptr != NULL);

    fprintf(fptr,"%s\n", name);
    fprintf(fptr,"%d\n", score);
    fclose(fptr);
}


void show_best_score_game(char path[]){
    vec_t SCORE;
    memset(&SCORE, 0, sizeof(int));
    assert(!init(&SCORE, sizeof(int)));
    FILE *fptr;
    fptr = fopen(path, "r");

    assert(fptr != NULL);
    char name[100];
    int score = 1;
    while (!feof(fptr)){
        fscanf(fptr, "%s", name);
        fscanf(fptr, "%d", &score);
        append(&SCORE, &score);
    }

    sort(&SCORE, (cmpfn) compare_score);

    for (int i = 0; i < 10; i++){ int k;
        get(&SCORE, i, &k);
        printf("(score %d) - {%d}\n",i + 1, k);
    }
    fclose(fptr);
}