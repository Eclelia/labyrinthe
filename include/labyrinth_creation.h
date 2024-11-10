#ifndef LABYRINTH_CREATION_H
#define LABYRINTH_CREATION_H
#include "labyrinth.h"

#define NB_TRAP 4 //TODO to delete
#define NB_BONUS 6 //TODO to delete

#define RATIO_WALL_TO_BREAK 65
#define RATIO_BONUS 32
#define RATIO_TRAP (2/3)*RATIO_BONUS


#define DATA_PATH "data/"

Labyrinth* init_labyrinth(int row, int column);

void init_unformed_labyrinth(Labyrinth* labyrinth);

void create_labyrinth_path(Labyrinth* labyrinth);

void init_create_recursive_labyrinth_path(Labyrinth* labyrinth, int difficult);

void create_recursive_labyrinth_path(Labyrinth* labyrinth, int current_row, int current_column);

void pull_random_cell(Labyrinth lab, int* random_row, int* random_column);

void pull_breakable_wall(Labyrinth lab, int* random_row, int* random_column);

void unify_room_number(Labyrinth* labyrinth, int number_to_place, int number_to_replace);

int make_labyrinth_playable(Labyrinth* labyrinth);

void make_lab_unperfect(Labyrinth* labyrinth);

void add_score_mecanics(Labyrinth* labyrinth, int nb_bonus, int nb_trap);

void add_key_and_lock_door(Labyrinth* labyrinth);

void add_objects(Labyrinth* labyrinth, int nb_objet, CellType object_to_place);

Labyrinth* copy_labyrinth(Labyrinth labyrinth);

void destroy_labyrinth(Labyrinth* labyrinth);

void shuffle_neighbours(Lab_cell* neighbours, int size);

#endif