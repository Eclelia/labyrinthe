#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "labyrinth_creation.h"
#include "labyrinth.h"
#include "display.h"

Labyrinth* init_labyrinth(int row, int column){
    //TODO check if i and j is odd
    srand(time(NULL));
    Labyrinth* new_lab = malloc(sizeof(Labyrinth));
    new_lab->largeur = column;
    new_lab->longueur = row;
    new_lab->game = malloc(column*row*sizeof(int));
    return new_lab;
}

void init_unformed_labyrinth(Labyrinth* labyrinth){
    int id = 1;

    for(int i = 0; i < labyrinth->longueur; i++){
        for(int j = 0; j < labyrinth->largeur; j++){
            if(i%2 == 1 && j%2 == 1){
                set_cell(labyrinth, i, j, id);
                id++;
            }
            else{
                set_cell(labyrinth, i, j, 0);
            }
        }
    } 
}

void create_labyrinth_path(Labyrinth* labyrinth){
    int random_row;
    int random_column;
    int walls_to_break = ((labyrinth->largeur-1)/2 *(labyrinth->longueur-1)/2) -1;

    while (walls_to_break > 0){
        pull_breakable_wall(*labyrinth, &random_row, &random_column);

        int neighbours[4] = {
                    get_cell(*labyrinth, random_row, random_column -1),     //left
                    get_cell(*labyrinth, random_row, random_column +1),     //right
                    get_cell(*labyrinth, random_row +1, random_column),     //top
                    get_cell(*labyrinth, random_row -1, random_column)      //bottom
        };

        if(neighbours[0] == 0){ /*check if left cell is a wall*/
            if(neighbours[2] != neighbours[3]){ /*are top and bottom the same room*/
                set_cell(labyrinth, random_row, random_column, neighbours[2]);
                unify_room_number(labyrinth, neighbours[2], neighbours[3]); 
                walls_to_break -= 1;
            }
        }
        else {
            if(neighbours[0] != neighbours[1]){ /*are left and right the same room*/
                set_cell(labyrinth, random_row, random_column, neighbours[0]);
                unify_room_number(labyrinth, neighbours[0], neighbours[1]); 
                walls_to_break -= 1;
            }
        }
    }
    /*add door and exit*/
    make_labyrinth_playable(labyrinth);
}

void init_create_recursive_labyrinth_path(Labyrinth* labyrinth){
    int random_row;
    int random_column;

    pull_random_cell(*labyrinth, &random_row, &random_column);
    create_recursive_labyrinth_path(labyrinth, random_row, random_column);

    make_labyrinth_playable(labyrinth);
}

Lab_cell* init_lab_cell(Labyrinth lab, int row, int column){
    if (row > 0 && row < lab.longueur -1 && column > 0 && column < lab.largeur-1){
        Lab_cell* new_cell = malloc(sizeof(Lab_cell));
        new_cell->column = column;
        new_cell->row = row;

        return new_cell;
    }
    return NULL;
}

int get_possible_neighbours(Labyrinth labyrinth, int current_row, int current_column, Lab_cell* neighbours){
    int nb_of_neighbour = 0;

    Lab_cell* left_cell = init_lab_cell(labyrinth, current_row, current_column -2);     //left cell
    Lab_cell* right_cell = init_lab_cell(labyrinth, current_row, current_column +2);    //right cell
    Lab_cell* top_cell = init_lab_cell(labyrinth, current_row -2, current_column);      //top cell
    Lab_cell* bottom_cell = init_lab_cell(labyrinth, current_row +2, current_column);   //bottom cell
    if (left_cell != NULL){
        neighbours[nb_of_neighbour] = *left_cell;
        nb_of_neighbour++;
    }
    if (right_cell != NULL){
        neighbours[nb_of_neighbour] = *right_cell;
        nb_of_neighbour++;
    }
    if (top_cell != NULL){
        neighbours[nb_of_neighbour] = *top_cell;
        nb_of_neighbour++;
    }
    if (bottom_cell != NULL){
        neighbours[nb_of_neighbour] = *bottom_cell;
        nb_of_neighbour++;
    }
    free(top_cell);
    free(bottom_cell);
    free(left_cell);
    free(right_cell);

    shuffle_neighbours(neighbours, nb_of_neighbour);
    return nb_of_neighbour;
}

void create_recursive_labyrinth_path(Labyrinth* labyrinth, int current_row, int current_column){
    int cell_value = get_cell(*labyrinth, current_row, current_column);

    Lab_cell neighbours[4];
    int nb_of_neigbours = get_possible_neighbours(*labyrinth, current_row, current_column, neighbours);

    for(int direction = 0; direction< nb_of_neigbours; direction++){
        int direction_value = get_cell(*labyrinth, neighbours[direction].row, neighbours[direction].column);
        if(direction_value != cell_value){
            //set la value de la cellule à cell value
            set_cell(labyrinth, neighbours[direction].row, neighbours[direction].column, cell_value);
            //set mur a cell value
            int wall_row = (neighbours[direction].row + current_row)/2;
            int wall_column = (neighbours[direction].column + current_column)/2;
            set_cell(labyrinth, wall_row, wall_column, cell_value);

            display_game_with_player(*labyrinth, wall_column, wall_row, 1);

            //donner la nouvelle case à cell_value
            create_recursive_labyrinth_path(labyrinth, neighbours[direction].row, neighbours[direction].column);
        }
    }
    return; 
}


//Fisher-Yates algorithm
void shuffle_neighbours(Lab_cell* neighbours, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Lab_cell temp = neighbours[i];
        neighbours[i] = neighbours[j];
        neighbours[j] = temp;
    }
}

void pull_breakable_wall(Labyrinth lab, int* random_row, int* random_column){

    *random_row = 1 + rand() % (lab.longueur - 2);
    if(*random_row%2 == 0){
        /*ensures it's an odd number*/
        *random_column = (rand() % ((int)(lab.largeur - 2)/2)) *2 +1;
    }
    else{
        /*ensures it's an even number*/
        *random_column = (1 + rand() % ((int)(lab.largeur - 2)/2)) *2;
    }
}

void pull_random_cell(Labyrinth lab, int* random_row, int* random_column){
    /*ensures it's an odd number*/
    *random_row = (rand() % ((lab.longueur - 1)/2)) *2 +1;
    *random_column = (rand() % ((lab.largeur - 1)/2)) *2 +1;
}

void unify_room_number(Labyrinth* labyrinth, int number_to_place, int number_to_replace){
    for(int i = 0; i < (labyrinth->longueur); i++){
        for(int j = 0; j < labyrinth->largeur; j++){
            if(get_cell(*labyrinth, i, j) == number_to_replace){
                set_cell(labyrinth, i, j, number_to_place);
            }
        }
    } 
}

int make_labyrinth_playable(Labyrinth* labyrinth){
    set_cell(labyrinth, 0, 1, PLAYER);
    set_cell(labyrinth, labyrinth->longueur -1 , labyrinth->largeur - 2, EXIT);
    return 0;
}

void destroy_labyrinth(Labyrinth* labyrinth){
    free(labyrinth->game);
    free(labyrinth);
}
