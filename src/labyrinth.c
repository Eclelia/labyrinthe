#include "labyrinth.h"

#include <stdio.h>

int get_cell(Labyrinth lab, int i, int j){
    //check que i et j soient dedans
    return lab.game[i*lab.largeur+j];
}

void set_cell(Labyrinth* lab, int i, int j, int value){
    //check que i et j soient dedans
    lab->game[(i*lab->largeur)+j] = value;
}