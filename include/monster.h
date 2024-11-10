#ifndef MONSTER_H
#define MONSTER_H

#include "game_struct.h"

#define RATIO_GHOST 65
#define RATIO_TROLL(nb_bonuses) ((1/3)*nb_bonuses) 

typedef enum{
    GHOST_P = -10,
    TROLL_P = -10,
} Penality;

struct Monster{
    int column;
    int row;
    int current_column;
    int current_row;
    CellType type;
    Penality penalty;
};

Monster* create_monster(int row, int column, CellType type, Penality penalty);

Monster* create_ghost(int row, int column);

Monster* create_troll(int row, int column);

void move_monsters(Labyrinth* lab);

int move_ghost(Labyrinth* lab, Monster* monster);

int move_troll(Labyrinth* lab, Monster* monster);

void add_monsters(Labyrinth* lab);

void add_ghost(Labyrinth* lab);

void add_troll(Labyrinth* lab, int nb_bonuses);

void destroy_monster(Monster* monster);

#endif