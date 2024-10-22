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
                printf(" o ");
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


void display_game_square(Labyrinth lab){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);
            if(cell_value > 0){ //if not a wall
                printf("   ");
            }
            else if(cell_value == -1){ // the player
                printf(" o ");
            } 
            else if(cell_value == -2){ // the exit
                printf("   ");
            } 
            else{
                printf(WHITE_HIGHLIGHT "   " ENDCOLOR);
            }
        }
        printf("\n");   
    }
}

void display_menu(){
    printf( BOLD
ORANGE " _           _                _       _   _     \n"
ORANGE "| |         | |              (_)     | | | |    \n"
ORANGE  "| |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  \n"
GREEN  "| |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ \n"
GREEN   "| |___| (_| | |_) | |_| | |  | | | | | |_| | | |\n"
BLUE   "\\_____/\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|\n"
BLUE   "                    __/ |                       \n"
BLUE   "                   |___/                        \n" 
ORANGE"C/c : Créer un labyrinthe\n"
"L/l : Charger un labyrinthe\n"
"P/p : Jouer\n"
"Q/q : Quitter\n" ENDCOLOR);
}