#include <stdio.h>
#include "display.h"
#include "labyrinth.h"

void display_game(Labyrinth lab){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);
            if(cell_value > 0){ //if not a wall
                printf("%2d ", cell_value);
            }
            else if(cell_value == -1){ // the player
                printf(" O ");
            } 
            else if(cell_value == -2){ // the exit
                printf("   ");
            } 
            else{
                printf(" # ");
            }
        }
        printf("\n");   
    }
}