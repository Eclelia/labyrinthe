#ifndef LABYRINTH_CREATION_H
#define LABYRINTH_CREATION_H
#include "labyrinth.h"

Labyrinth* init_labyrinth(int row, int column);

void init_unformed_labyrinth(Labyrinth* labyrinth);

void create_labyrinth_path(Labyrinth* labyrinth);

void init_create_recursive_labyrinth_path(Labyrinth* labyrinth);

void create_recursive_labyrinth_path(Labyrinth* labyrinth, int current_row, int current_column);

void pull_random_cell(Labyrinth lab, int* random_row, int* random_column);

void pull_breakable_wall(Labyrinth lab, int* random_row, int* random_column);

void unify_room_number(Labyrinth* labyrinth, int number_to_place, int number_to_replace);

int make_labyrinth_playable(Labyrinth* labyrinth);

void destroy_labyrinth(Labyrinth* labyrinth);

void shuffle_neighbours(Lab_cell* neighbours, int size);

#endif