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


int get_cell(Labyrinth lab, int i, int j);

void set_cell(Labyrinth* lab, int i, int j, int value);

#endif