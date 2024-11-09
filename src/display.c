#define _DEFAULT_SOURCE //needed for usleep to be imported correctly

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "display.h"
#include "labyrinth.h"

void display_game(Labyrinth lab){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);
            if(cell_value > WALL){ //if not a wall
                printf("%2d ", cell_value);
            }
            else if(cell_value == PLAYER){ 
                printf(" o ");
            } 
            else if(cell_value == EXIT){
                printf("   ");
            }
            else if(cell_value == CLOSED_EXIT){
                printf("xxx");
            } 
            else if(cell_value == KEY){
                printf(YELLOW " K " ENDCOLOR);
            }
            else if(cell_value == BONUS_CELL){
                printf(GREEN_HIGHLIGHT " B " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " T " ENDCOLOR);
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
            if(cell_value > WALL){ //if not a wall
                printf("   ");
            }
            else if(cell_value == PLAYER){ 
                printf(" o ");
            } 
            else if(cell_value == EXIT){ 
                printf("   ");
            } 
            else if(cell_value == CLOSED_EXIT){ 
                printf("xxx");
            } 
            else if(cell_value == KEY){
                printf(YELLOW " K " ENDCOLOR);
            }
            else if(cell_value == BONUS_CELL){
                printf(GREEN_HIGHLIGHT " B " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " T " ENDCOLOR);
            } 
            else{
                printf(WHITE_HIGHLIGHT "   " ENDCOLOR);
            }
        }
        printf("\n");   
    }
}

void display_game_with_player(Labyrinth lab, int column, int row, int wait){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);
            if(i == row && j == column){
                printf(BLUE_HIGHLIGHT "   " ENDCOLOR);
            }
            else if(cell_value > WALL){ //if not a wall
                printf("   ");
            }
            else if(cell_value == PLAYER){ // the player
                printf(" o ");
            } 
            else if(cell_value == EXIT){ // the exit
                printf("   ");
            } 
            else if(cell_value == CLOSED_EXIT){ // the exit
                printf("xxx");
            } 
            else if(cell_value == KEY){
                printf(YELLOW " K " ENDCOLOR);
            }
            else if(cell_value == BONUS_CELL){
                printf(GREEN_HIGHLIGHT " B " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " T " ENDCOLOR);
            } 
            else{
                printf(WHITE_HIGHLIGHT "   " ENDCOLOR);
            }
        }
        printf("\n");   
    }
    if(wait){
        usleep(30000);
    }
    system("clear");
}

void ncurses_display_game_state(Labyrinth lab, int column, int row, int score){
    clear();
    use_default_colors();
    start_color();

    // Definition of ncurses color pairs
    init_pair(PLAYER_PAIR, COLOR_WHITE, COLOR_BLUE);   // Joueur en surbrillance bleue
    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_WHITE);    // Mur blanc sur blanc
    init_pair(EXIT_PAIR, COLOR_BLACK, COLOR_GREEN);    // Sortie sur fond vert
    init_pair(KEY_PAIR, COLOR_YELLOW, -1);    // Key yellow on black
    init_pair(BONUS_PAIR, COLOR_GREEN, COLOR_GREEN);   // Bonus in green
    init_pair(TRAP_PAIR, COLOR_RED, COLOR_RED);        // Trap in red

    int i;
    for(i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);

            int y = i;
            int x = j * 3;

            if(i == row && j == column){
                attron(COLOR_PAIR(PLAYER_PAIR));
                mvprintw(y, x, "   "); // Position du joueur
                attroff(COLOR_PAIR(PLAYER_PAIR));
            }
            else if(cell_value > WALL || cell_value == PLAYER){ //if not a wall
                mvprintw(y, x, "   ");
            }
            else if(cell_value == EXIT){ // the exit
                attron(COLOR_PAIR(EXIT_PAIR));
                mvprintw(y, x, " E ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            } 
            else if(cell_value == CLOSED_EXIT){
                attron(COLOR_PAIR(EXIT_PAIR));
                mvprintw(y, x, "xxx");
                attroff(COLOR_PAIR(EXIT_PAIR));
            } 
            else if(cell_value == KEY){
                attron(COLOR_PAIR(KEY_PAIR));
                mvprintw(y, x, " K ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            }
            else if(cell_value == BONUS_CELL){
                attron(COLOR_PAIR(BONUS_PAIR));
                mvprintw(y, x, " B ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            }
            else if(cell_value == TRAP_CELL){
                attron(COLOR_PAIR(TRAP_PAIR));
                mvprintw(y, x, " T ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            } 
            else{
                attron(COLOR_PAIR(WALL_PAIR));
                mvprintw(y, x, "   ");
                attroff(COLOR_PAIR(WALL_PAIR));
            }
        }  
    }
    mvprintw(i+1, 0, "SCORE : %d\t Bouger: haut:z, gauche:q, bas:s, droite:d", score);
    mvprintw(i+2, 0, "Quitter : ESC");
    refresh();
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
ORANGE"1 : Créer un labyrinthe\n"
"2 : Charger un labyrinthe\n"
"3 : Jouer\n"
"4 : Leaderboard\n"
"5 : Quitter\n" ENDCOLOR);
}