#include <stdlib.h>
#include "labyrinth_creation.h"

Labyrinth* init_labyrinth(int largeur, int longueur){
    //malloc pour la struct et malloc pour les 2 tableaux
    Labyrinth* new_lab = malloc(sizeof(Labyrinth));
    new_lab->largeur = largeur;
    new_lab->longueur = longueur;
    new_lab->game = malloc(largeur*longueur*sizeof(char));

    return new_lab;
}

void init_unformed_labyrinth(Labyrinth* labyrinth);

void create_labyrinth_path(Labyrinth* labyrinth);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int unify_room_number(Labyrinth*, int number_to_place, int number_to_replace);

int make_labyrinth_playable(Labyrinth* labyrinth);

char get_cell(Labyrinth game, int i, int j){
    //check que i et j soient dedans
    return '#';
}
