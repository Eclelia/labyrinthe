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