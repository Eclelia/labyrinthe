#include "labyrinth.h"

#include <stdio.h>

int get_cell(Labyrinth lab, int i, int j){
    //check que i et j soient dedans
    return lab.game[i*lab.largeur+j];
}

void set_cell_value(Labyrinth* lab, int i, int j, int value){
    //check que i et j soient dedans
    printf("i = %d\t", i);
    printf("j = %d\t", j);
    printf("value = %d\t", value);
    printf("largeur = %d\t", lab->largeur);
    printf("longueur = %d\t", lab->longueur);

    printf("emplacement = %d\n", (i*lab->largeur)+j);

    lab->game[(i*lab->largeur)+j] = value;
}