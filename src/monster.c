#include <stdlib.h>
#include <stdio.h>

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
    int nb_bonuses = get_nb_bonus(*lab);
    int nb_trolls = RATIO_TROLL(nb_bonuses);

    int nb_monsters = nb_ghosts + nb_trolls;

    printf("%d\n", nb_bonuses);
    printf("%d\n", nb_trolls);

    lab->monsters = malloc(sizeof(Monster) * nb_monsters);
    
    for(int i = 0; i <nb_ghosts; i++){
        add_ghost(lab);
    }

    for(int i = 0; i <nb_trolls; i++){
        add_troll(lab, nb_bonuses);
    }

    for(int i = 0; i < lab->n_monsters; i++){
        printf("monstre n°%d: [%d %d] %d\n", i, lab->monsters[i].column, lab->monsters[i].row, lab->monsters[i].type);
    }
}

void add_ghost(Labyrinth* lab) {
    int random_row, random_column;
    int pulled_cell;
    do{
        random_row = rand() % lab->longueur;
        random_column = rand() % lab->largeur;
        pulled_cell = get_cell(*lab, random_row, random_column);
    }while(pulled_cell != PLAYER && pulled_cell != EXIT && pulled_cell != CLOSED_EXIT);

    Monster* new_ghost = create_ghost(random_row, random_column);
    lab->monsters[lab->n_monsters] = *new_ghost;
    lab->n_monsters = lab->n_monsters+1;
}

void add_troll(Labyrinth* lab, int nb_bonuses) { //TODO 2 trolls peuvent spawn sur le même bonus
    int nth_bonus = (rand() % nb_bonuses) +1;

    int bonus_row, bonus_column;
    get_nth_bonus(*lab, nth_bonus, &bonus_row, &bonus_column);
    
    Monster* new_troll = create_troll(bonus_row, bonus_column);
    lab->monsters[lab->n_monsters] = *new_troll;
    lab->n_monsters = lab->n_monsters+1;
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

//TODO "distance_from_spawn"

void destroy_monster(Monster* monster) {
    free(monster);
}