#ifndef LABYRINTH_CREATION_H
#define LABYRINTH_CREATION_H
#include "labyrinth.h"

Labyrinth* init_labyrinth(int largeur, int longueur);

void init_unformed_labyrinth(Labyrinth* labyrinth);

void create_labyrinth_path(Labyrinth* labyrinth);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int is_same_room_vertically(Labyrinth* labyrinth, int i, int j);

int unify_room_number(Labyrinth*, int number_to_place, int number_to_replace);

int make_labyrinth_playable(Labyrinth* labyrinth);

#endif