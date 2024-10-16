#include <stdlib.h>
#include "labyrinth_creation.h"
#include "labyrinth.h"

Labyrinth* init_labyrinth(int largeur, int longueur){
    //malloc pour la struct et malloc pour les 2 tableaux
    Labyrinth* new_lab = malloc(sizeof(Labyrinth));
    new_lab->largeur = largeur;
    new_lab->longueur = longueur;
    new_lab->game = malloc(largeur*longueur*sizeof(int));
    return new_lab;
}

void init_unformed_labyrinth(Labyrinth* labyrinth){
    int id = 1;

    for(int i = 0; i < (labyrinth->longueur); i++){
        for(int j = 0; j < labyrinth->largeur; j++){
            if(i%2 == 1 && j%2 == 1){
                set_cell_value(labyrinth, i, j, id);
                id++;
            }
            else{
                set_cell_value(labyrinth, i, j, 0);
            }
        }
    } 
}

void create_labyrinth_path(Labyrinth* labyrinth);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int unify_room_number(Labyrinth*, int number_to_place, int number_to_replace);

int make_labyrinth_playable(Labyrinth* labyrinth);
