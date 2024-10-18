#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "labyrinth_creation.h"
#include "labyrinth.h"
#include "display.h"

Labyrinth* init_labyrinth(int largeur, int longueur){
    srand(time(NULL));
    Labyrinth* new_lab = malloc(sizeof(Labyrinth));
    new_lab->largeur = largeur;
    new_lab->longueur = longueur;
    new_lab->game = malloc(largeur*longueur*sizeof(int));
    return new_lab;
}

void init_unformed_labyrinth(Labyrinth* labyrinth){
    int id = 1;

    for(int i = 0; i < (labyrinth->longueur); i++){
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
        /*system("clear");
        printf("walls to break : %d\n", walls_to_break);
        display_game(*labyrinth);*/

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

int is_same_room_vertically(Labyrinth labyrinth, int i, int j){
    //TODO expliquer au prof dileme
    //TODO check que i et j pas seg fault
    return (get_cell(labyrinth, i-1, j) == get_cell(labyrinth, i+1, j));
}

int is_same_room_horizontally(Labyrinth labyrinth, int i, int j){
    //TODO check que i et j pas seg fault
    return (get_cell(labyrinth, i, j-1) == get_cell(labyrinth, i, j+1));

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
    set_cell(labyrinth, 0, 1, -1); //adds player
    set_cell(labyrinth, labyrinth->longueur, labyrinth->largeur - 1, -2); //adds player
    return 0;
}

void destroy_labyrinth(Labyrinth* labyrinth){
    free(labyrinth->game);
    free(labyrinth);
}
