#include "labyrinth.h"

#include <stdio.h>

int get_cell(Labyrinth lab, int i, int j){
    if (i >= 0 && i < lab.longueur && j >= 0 && j < lab.largeur){
        return lab.game[i*lab.largeur+j];
    }
    return UNDEFINED;
}

int set_cell(Labyrinth* lab, int i, int j, int value){
    if (i >= 0 && i < lab->longueur && j >= 0 && j < lab->largeur){
        lab->game[i*lab->largeur+j] = value;
        return 0;
    }
    return -1;
}

int get_nb_bonus(Labyrinth lab){
    int nb_bonuses = 0;
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            if(get_cell(lab, i, j) == BONUS_CELL){
                nb_bonuses++;
            }
        }
    }
    return nb_bonuses;
}

int get_nth_bonus(Labyrinth lab, int nth, int* row, int* column){
    int nb_bonuses = 0;
    int found = 0;
    for(int i = 0; i < lab.longueur  && !found; i++){
        for (int j = 0; j < lab.largeur  && !found; j++){ 
            if(get_cell(lab, i, j) == BONUS_CELL){
                nb_bonuses++;
                if(nb_bonuses == nth){
                    *row = i;
                    *column = j;
                    found = 1;
                }
            }
        }
    }
    return found;
}

void empty_buffer(){
    while ((getchar()) != '\n');
}