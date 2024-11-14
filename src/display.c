#define _DEFAULT_SOURCE //needed for usleep to be imported correctly

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "display.h"
#include "labyrinth.h"
#include "leaderboard.h"

void display_game(Labyrinth lab){
    for(int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){ 
            int cell_value = get_cell(lab, i, j);
            if(cell_value > WALL){ //if not a wall
                printf("%2d ", cell_value);
            }
            else if(cell_value == ENTRY){ 
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
                printf(GREEN_HIGHLIGHT " o " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " x " ENDCOLOR);
            }
            else if(cell_value == GHOST){
                printf(CYAN DARK_CYAN_HIGHLIGHT "(¨)" ENDCOLOR);
            } 
            else if(cell_value == TROLL){
                printf(ORANGE DARK_RED_HIGHLIGHT "`o´" ENDCOLOR);
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
            else if(cell_value == ENTRY){ 
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
                printf(GREEN_HIGHLIGHT " o " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " x " ENDCOLOR);
            }
            else if(cell_value == GHOST){
                printf(CYAN DARK_CYAN_HIGHLIGHT "(¨)" ENDCOLOR);
            } 
            else if(cell_value == TROLL){
                printf(ORANGE DARK_RED_HIGHLIGHT "`o´" ENDCOLOR);
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
            else if(cell_value == ENTRY){ // the entry
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
                printf(GREEN_HIGHLIGHT " o " ENDCOLOR);
            }
            else if(cell_value == TRAP_CELL){
                printf(RED_HIGHLIGHT " x " ENDCOLOR);
            } 
            else if(cell_value == GHOST){
                printf(CYAN DARK_CYAN_HIGHLIGHT "(¨)" ENDCOLOR);
            } 
            else if(cell_value == TROLL){
                printf(ORANGE DARK_RED_HIGHLIGHT "`o´" ENDCOLOR);
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
    init_ncurses_colors();

    int colonnes = 54;

    int player_offset_column = (column > colonnes/2) ? column - (colonnes/2) : 0;
    int player_offset_row = (row > (LINES/2)) ? row - (LINES/2) : 0;

    int i;
    for(i = player_offset_row; i < lab.longueur && i < LINES+player_offset_row; i++){
        for (int j = player_offset_column; j < lab.largeur && j < colonnes+player_offset_column; j++){ 
            int cell_value = get_cell(lab, i, j);

            int y = i - player_offset_row;
            int x = (j - player_offset_column) * 3;

            if(cell_value > WALL || cell_value == ENTRY){ //if not a wall
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
                mvprintw(y, x, " o ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            }
            else if(cell_value == TRAP_CELL){
                attron(COLOR_PAIR(TRAP_PAIR));
                mvprintw(y, x, " x ");
                attroff(COLOR_PAIR(EXIT_PAIR));
            } 
            else{
                attron(COLOR_PAIR(WALL_PAIR));
                mvprintw(y, x, "   ");
                attroff(COLOR_PAIR(WALL_PAIR));
            }
        }  
    }
    //display monsters
    for(int k = 0; k < lab.n_monsters; k++){
        Monster mon = lab.monsters[k]; 
        int m_row = mon.current_row - player_offset_row;
        int m_column = (mon.current_column - player_offset_column)*3;
        switch (mon.type){
        case GHOST :
            attron(COLOR_PAIR(GHOST_PAIR));
            mvprintw(m_row, m_column, "(\")");
            attroff(COLOR_PAIR(EXIT_PAIR));
            break;
        case TROLL :
            attron(COLOR_PAIR(TROLL_PAIR));
            mvprintw(m_row, m_column, "'o'");
            attroff(COLOR_PAIR(EXIT_PAIR));
            break;
        default : 
            attron(COLOR_PAIR(TROLL_PAIR));
            mvprintw(0, 0, "'o'");
            attroff(COLOR_PAIR(EXIT_PAIR));
            break;
        }
    }
    //display_player (so they're on top)
    attron(COLOR_PAIR(PLAYER_PAIR));
    mvprintw(row - player_offset_row, (column - player_offset_column)*3, "   "); // Position du joueur
    attroff(COLOR_PAIR(PLAYER_PAIR));

    //display GUI
    display_GUI(score);

    //mvprintw(LINES - 4, 0, "OFFSET_COL : %d\t OFFSET_LINE : %d \t COLS : %d \t LINES : %d", player_offset_column, player_offset_row, colonnes, LINES);
    refresh();
}

void display_menu(){
    printf( BOLD
YELLOW " _           _                _       _   _     \n"
YELLOW "| |         | |              (_)     | | | |    \n"
YELLOW "| |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  \n"
GREEN  "| |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ \n"
GREEN  "| |___| (_| | |_) | |_| | |  | | | | | |_| | | |\n"
BLUE   "\\_____/\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|\n"
BLUE   "                    __/ |                       \n"
BLUE   "                   |___/                        \n" 
YELLOW"1 : Créer un labyrinthe\n"
"2 : Charger un labyrinthe\n"
"3 : Jouer\n"
"4 : Leaderboard\n"
"5 : Quitter\n" ENDCOLOR);
}

void display_win(){ //only in ncurses mode
    init_pair(WIN_PAIR, COLOR_BLUE, -1);
    attron(COLOR_PAIR(WIN_PAIR));
    mvprintw(0,0,
"__  __                                       __\n"
"\\ \\/ /___  __  __   _      ______  ____     / /\n"
" \\  / __ \\/ / / /  | | /| / / __ \\/ __ \\   / / \n"
" / / /_/ / /_/ /   | |/ |/ / /_/ / / / /  /_/  \n"
"/_/\\____/\\__,_/    |__/|__/\\____/_/ /_/  (_)   \n");
    attroff(COLOR_PAIR(WIN_PAIR));

    init_pair(KEY_PAIR, COLOR_YELLOW, -1);
    mvprintw(7, 0, "Veuillez appuyer sur ESC pour continuer.\n");
    attroff(COLOR_PAIR(KEY_PAIR));

    refresh();
}

void display_highscore_message(){
    char* animation_color[5] = {BLUE, BLUE, BLUE, GREEN, YELLOW};
    for(int i = 0; i < 3; i++){
        system("clear");
        printf(
        "%s    _   __                __  ___       __                                 __\n"
        "   / | / /__ _      __   / / / (_)___ _/ /_  ______________  ________     / /\n" ENDCOLOR
        "%s  /  |/ / _ \\ | /| / /  / /_/ / / __ `/ __ \\/ ___/ ___/ __ \\/ ___/ _ \\   / / \n"
        " / /|  /  __/ |/ |/ /  / __  / / /_/ / / / (__  ) /__/ /_/ / /  /  __/  /_/  \n" ENDCOLOR
        "%s/_/ |_/\\___/|__/|__/  /_/ /_/_/\\__, /_/ /_/____/\\___/\\____/_/   \\___/  (_)   \n"
        "                              /____/                                         \n" ENDCOLOR, 
        animation_color[i+2], animation_color[i+1], animation_color[i]);
        usleep(250000);
    }
}

void display_leaderboard(Leaderboard lb){
    //system("clear");
    printf(YELLOW
        "╔═════════════════════════════════════════════════════════════╗\n"
	    "║_.~\"~._.~\"~._.~\"~._.~\"~._Leaderboard_.~\"~._.~\"~._.~\"~._.~\"~..║\n"
	    "╠══════╦══════════════════════════════════════╦═══════════════╣\n"
	    "║ Rank ║                 Name                 ║     Score     ║\n"
	    "╠══════╬══════════════════════════════════════╬═══════════════╣\n"
    );
	
	for(int i = 0; i<lb.nb_of_scores; i++){
		printf("║ %4d ║ %36s ║ %13d ║\n", i+1, lb.score_list[i].name, lb.score_list[i].score);
	}
	printf("╚══════╩══════════════════════════════════════╩═══════════════╝\n" ENDCOLOR);
}

void display_GUI(int score){
    mvprintw(LINES - 4, 0, "SCORE : %d\t Bouger: haut:z, gauche:q, bas:s, droite:d\t Quitter : ESC", score);
    mvprintw(LINES - 3, 0, "\tSortie : ");
    attron(COLOR_PAIR(EXIT_PAIR)); printw(" E "); attroff(COLOR_PAIR(EXIT_PAIR));
    printw("\tSortie fermée : ");
    attron(COLOR_PAIR(EXIT_PAIR)); printw("xxx"); attroff(COLOR_PAIR(EXIT_PAIR));
    printw("\t Clé (ouvre la porte): ");
    attron(COLOR_PAIR(KEY_PAIR)); printw(" K"); attroff(COLOR_PAIR(EXIT_PAIR));

    mvprintw(LINES - 2, 0, "MALUS : Piege :  ");
    attron(COLOR_PAIR(TRAP_PAIR)); printw(" x "); attroff(COLOR_PAIR(EXIT_PAIR));
    printw("\tFantôme : ");
    attron(COLOR_PAIR(GHOST_PAIR)); printw("(\")"); attroff(COLOR_PAIR(EXIT_PAIR));
    printw("\t\tOgre :");
    attron(COLOR_PAIR(TROLL_PAIR)); printw("'o'"); attroff(COLOR_PAIR(EXIT_PAIR));

    mvprintw(LINES - 1, 0, "BONUS : ");
    attron(COLOR_PAIR(BONUS_PAIR)); printw(" o "); attroff(COLOR_PAIR(EXIT_PAIR)); 
}

void init_ncurses_colors(){
    use_default_colors();
    start_color();

    init_color(COLOR_RED, 1000, 372, 372);
    init_color(COLOR_GREEN, 0, 529, 0);
    init_color(COLOR_ORANGE, 1000, 529, 0);
    init_color(COLOR_DARK_RED, 372, 0, 0);
    init_color(COLOR_CYAN, 372, 1000, 686);
    init_color(COLOR_DARK_CYAN,0, 372, 372);

    // Definition of ncurses color pairs
    init_pair(PLAYER_PAIR, COLOR_WHITE, COLOR_BLUE);   // Joueur en surbrillance bleue
    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_WHITE);    // Mur blanc sur blanc
    init_pair(EXIT_PAIR, COLOR_WHITE, COLOR_GREEN);    // Sortie sur fond vert
    init_pair(KEY_PAIR, COLOR_YELLOW, -1);             // Key yellow on black
    init_pair(BONUS_PAIR, COLOR_WHITE, COLOR_GREEN);   // Bonus in green
    init_pair(TRAP_PAIR, COLOR_BLACK, COLOR_RED);      // Trap in red
    init_pair(TROLL_PAIR, COLOR_ORANGE, COLOR_DARK_RED);// Troll in orange
    init_pair(GHOST_PAIR, COLOR_CYAN, COLOR_DARK_CYAN); // Ghost in cyan
}