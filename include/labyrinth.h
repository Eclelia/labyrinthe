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

int get_cell(Labyrinth lab, int i, int j);

int set_cell(Labyrinth* lab, int i, int j, int value);

#endif