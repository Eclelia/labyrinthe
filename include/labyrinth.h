#ifndef LABYRINTH_H
#define LABYRINTH_H
#define LARGEUR 11
#define LONGUEUR 25

struct Labyrinth{
    int* game;
    int largeur; //TODO refacto les largeur en column
    int longueur; //TODO refacto les longueur en row
}; 
typedef struct Labyrinth Labyrinth;

typedef struct Labyrinth_cell{
    int row;
    int column;
} Lab_cell;

typedef enum{
    PATH = 1,
    WALL = 0,
    UNDEFINED = -10,
    PLAYER = -1,
    EXIT = -2,
    CLOSED_EXIT = -3,
    KEY = -4,
    BONUS_CELL = -5,
    TRAP_CELL = -6,
    GHOST = -7,
    TROLL = -8
} CellType;

int get_cell(Labyrinth lab, int i, int j);

int set_cell(Labyrinth* lab, int i, int j, int value);

#endif