#include <stdlib.h>
#include <stdio.h>
#include "labyrinth.h"
#include "display.h"
#include "labyrinth_creation.h"
#include "game.h"
#include "leaderboard.h"

int main()
{
    /*Labyrinth* lab = init_labyrinth(15, 13);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab);

    display_game_square(*lab); 
    
    destroy_labyrinth(lab);

    Leaderboard* lb = init_leaderboard();
    P_score* pc = init_player_score("Paul", 3000);
    P_score* pc2 = init_player_score("Erathostenes", -100);
    lb->score_list[0] = *pc;
    lb->nb_of_scores = 2;
    lb->score_list[1] = *pc2;
    display_lb(*lb);
    save_leaderboard(*lb, "7x7");
    Leaderboard* lb_2 = load_leaderboard("7x7");
    display_lb(*lb_2);*/

    handle_game();
}
