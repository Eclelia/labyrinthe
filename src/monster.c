#include <stdlib.h>

#include "monster.h"
#include "labyrinth.h"

Monster* create_monster(int row, int column, CellType type, Penality penalty) {
    Monster* new_monster = malloc(sizeof(Monster));
    new_monster->row = row;
    new_monster->column = column;
    new_monster->current_row = row;
    new_monster->current_column = column;
    new_monster->type = type;
    new_monster->penalty = penalty;
    return new_monster;
}

Monster* create_ghost(int row, int column) {
    return create_monster(row, column, GHOST, GHOST_P);
}

Monster* create_troll(int row, int column) {
    return create_monster(row, column, TROLL, TROLL_P);
}

void move_monsters(Labyrinth* lab) {
    for (int i = 0; i < lab->n_monsters; i++) {
        Monster* monster = &lab->monsters[i];
        switch (monster->type){
        case GHOST:
            move_ghost(lab, monster);break;
        default :
            move_troll(lab, monster);break; //by default, all monsters follow the same logic as trolls
        }
    }
}

void add_monsters(Labyrinth* lab) {
    int nb_ghosts = (lab->largeur * lab->longueur)/RATIO_GHOST;
    int nb_bonuses;//TODO get nb bonus
    int nb_trolls = 0;//TODO def nb_troll en fonction de nb_bonus

    lab->n_monsters = nb_ghosts + nb_trolls;
    lab->monsters = malloc(sizeof(Monster) * lab->n_monsters);
    
    for(int i = 0; i <nb_ghosts; i++){
        add_ghost(lab);
    }

    for(int i = 0; i <nb_trolls; i++){
        add_troll(lab, nb_bonuses);
    }
}

void add_ghost(Labyrinth* lab) {
    //get des coordonnée aléatoire
    //if (next_cell != UNDEFINED && next_cell != EXIT && next_cell != CLOSED_EXIT) {
        //creer le mob
        //l'ajouter à la liste de monstre
}

void add_troll(Labyrinth* lab, int nb_bonuses) {
    //get nth bonus (le nth etant alé entre 0 et nb_bonus-1)
    //get les coordonnées du bonus
    //creer l'objet monstre sur le bonus
    //add ce monstre à la liste
}

//it's possible that a ghost doesn't move
int move_ghost(Labyrinth* lab, Monster* monster) {
    int d_column = rand() % 3 - 1; //go left or right or not
    int d_row = rand() % 3 - 1; //go up or down or not

    int next_column = monster->column + d_column;
    int next_row = monster->row + d_row;

    int next_cell = get_cell(*lab, next_row, next_column);
    if (next_cell != UNDEFINED && next_cell != EXIT && next_cell != CLOSED_EXIT) { //can move //TODO check si bon ordre
        monster->row = next_row;
        monster->column = next_column;
    }
    return GHOST;
}

//it's possible that a troll doesn't move
int move_troll( Labyrinth* lab, Monster* monster) { //TODO : l'empecher de trop s'éloigner du bonus
    int d_column = rand() % 3 - 1; //go left or right or not
    int d_row = rand() % 3 - 1; //go up or down or not

    int next_column = monster->column + d_column;
    int next_row = monster->row + d_row;

    int next_cell = get_cell(*lab, next_row, next_column);
    if (next_cell != UNDEFINED && next_cell != WALL && next_cell != EXIT && next_cell != CLOSED_EXIT) { //can move //TODO check si bon ordre
        monster->row = next_row;
        monster->column = next_column;
    }
    return TROLL;
}

void destroy_monster(Monster* monster) {
    free(monster);
}