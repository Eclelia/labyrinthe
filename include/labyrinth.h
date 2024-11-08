#ifndef LABYRINTH_H
#define LABYRINTH_H
#define LARGEUR 11
#define LONGUEUR 25

struct Labyrinth{
    int* game;
    int largeur;
    int longueur;
}; 
typedef struct Labyrinth Labyrinth;

typedef struct Labyrinth_cell{
    int row;
    int column;
} Lab_cell;

typedef enum{
    UNDEFINED = -10,
    WALL = 0,
    PLAYER = -1,
    EXIT = -2,
    CLOSED_EXIT = -3,
} CellType;

int get_cell(Labyrinth lab, int i, int j);

int set_cell(Labyrinth* lab, int i, int j, int value);

#endif