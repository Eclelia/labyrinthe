#include <stdio.h>
#include "display.h"
#include "labyrinth.h"

void display_game(Labyrinth lab){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int call_value = get_cell(lab, i, j);
            if(call_value > 0){ //if not a wall
                printf("%2d ", call_value);
            }
            else{
                printf(" # ");
            }
        }
        printf("\n");   
    }
}