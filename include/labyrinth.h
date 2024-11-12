#ifndef LABYRINTH_H
#define LABYRINTH_H
#define LARGEUR 11
#define LONGUEUR 25
#define STARTING_ROW 0
#define STARTING_COLUMN 1

#include "game_struct.h"
#include "monster.h"

struct Labyrinth{
    int* game;
    int largeur; //TODO refacto les largeur en column
    int longueur; //TODO refacto les longueur en row
    int n_monsters;
    Monster* monsters;
};

struct Labyrinth_cell{
    int row;
    int column;
};

int get_cell(Labyrinth lab, int i, int j);

int get_nb_bonus(Labyrinth lab);

int get_nth_bonus(Labyrinth lab, int nth, int* row, int* column);

int set_cell(Labyrinth* lab, int i, int j, int value);

void empty_buffer();

#endif