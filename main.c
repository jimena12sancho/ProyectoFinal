#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "libgenericgame.h"

int main() {
    srand(time(0));
    int option_mainmenu = 0;

    do{
        printf("1- Iniciar Juego Nuevo\n"
               "2- Ver las 10 mejores puntuaciones\n"
               "3- Salir \n"
               "Inserte Opcion: ");
        scanf("%d", &option_mainmenu);
        if(inRange(1, 2, option_mainmenu)){
            if(option_mainmenu == 1){
                vec_t deck = init_deck(4, 13),
                        stack_deck = init_deck(0, 0);

                shuffle_deck(&deck);
                struct player players[2];

                for (int i = 0; i < 2; ++i)
                    players[i] = init_player();
                bool cp = rand() % 2;

                players[0].name = malloc(100 * sizeof (char));
                players[1].name = malloc(100 * sizeof (char));

                printf("Jugador1, inserte su nombre: "); scanf("%s", players[0].name);
                printf("Jugador2, inserte su nombre: "); scanf("%s", players[1].name);
                //Repartir Cartas
                for (int i = 0; i < 2; ++i)
                    for (int card = 0; card < 10; ++card)
                        pushback_deck(&players[i].hand, popback_deck(&deck));

                int particular_option_user = 0;

                struct pcard top_stackd = popback_deck(&deck);

                pushback_deck(&stack_deck, top_stackd);
                bool SOMEONEWONTWIN = true;
                do{
                    bool current_player =  change_player(&cp);
                    card_fusion_game(players, deck, stack_deck, top_stackd, current_player);
                    printf("\nTe toca (%s) Que deseas hacer?", players[current_player].name);
                    printf("\n1-Robar del Mazo principal\n"
                           "2-Robar del Mazo de descarte\n"
                           "4-Anunciar Knock\n"
                           "Ingrese # de opcion: ");
                    scanf("%d", &particular_option_user);
                    if(inRange(1, 4, particular_option_user)){
                        switch (particular_option_user) {
                            case 1:{
                                struct pcard temp = popback_deck(&deck);
                                pushback_deck(&players[current_player].hand, temp);
                                cstatus_game_terminal(players, deck, stack_deck, top_stackd);
                                card_to_discard_game(&players[current_player], deck, &stack_deck, &top_stackd);
                                card_fusion_game(players, deck, stack_deck, top_stackd, current_player);
                                break;
                            }
                            case 2:{
                                if (stack_deck.size != 0)
                                    pushback_deck(&players[current_player].hand, top_stackd);
                                top_stackd = getpcard_deck(stack_deck, stack_deck.size - 2);
                                popback_deck(&stack_deck);
                                cstatus_game_terminal(players, deck, stack_deck, top_stackd);
                                card_to_discard_game(&players[current_player], deck, &stack_deck, &top_stackd);
                                card_fusion_game(players, deck, stack_deck, top_stackd, current_player);
                                break;
                            }
                            case 4:{
                                cstatus_game_terminal(players, deck, stack_deck, top_stackd);
                                int status = knock_alert_game(players, deck, stack_deck, top_stackd, &current_player, &SOMEONEWONTWIN);
                                if (status != -9999){
                                    printf("Gana la Ronda %s", players[current_player].name);
                                    saved_score_game("scoresaved.txt", players[current_player].name, status);
                                }
                                break;
                            }
                            default: break;
                        }
                    }
                    int scoredverified_gin = sum_current_deck(players[current_player].hand);
                    if( scoredverified_gin == 0){
                        printf("Gana la Ronda %s", players[current_player].name);
                        saved_score_game("scoresaved.txt", players[current_player].name, sum_current_deck(players[!current_player].hand) + 150);
                    }
                } while (SOMEONEWONTWIN);
            }
            else show_best_score_game("scoresaved.txt");
        }
    }while(option_mainmenu != 3);

    return 0;
}
