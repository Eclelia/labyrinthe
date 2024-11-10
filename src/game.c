#include "game.h"
#include "display.h"
#include "labyrinth.h"
#include "labyrinth_creation.h"
#include "labyrinth_file_helper.h"
#include "leaderboard.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void handle_game(){
    int menu_choice = MENU;
    Labyrinth* loaded_lab = NULL;
    char loaded_lab_name[NAME_SIZE];
    do{
        display_menu();
        scanf("%d", &menu_choice);
        while (getchar() != '\n');

        if(menu_choice == CREATE){
            loaded_lab = create_and_save();
            menu_choice = MENU;
        }
        else if(menu_choice == LOAD){
            loaded_lab = load_lab(loaded_lab_name); //TODO proposer une liste des lab enregistré (les *.cfg)
            if(loaded_lab == NULL){
                printf(RED_HIGHLIGHT "Fichier non trouvé ou corrompu" ENDCOLOR "\n");
            }
            else{
                display_game_square(*loaded_lab);
            }
            menu_choice = MENU;
        }
        else if(menu_choice == PLAY){
            if(loaded_lab == NULL){
                printf(RED_HIGHLIGHT "Veuillez d'abord charger un labyrinthe" ENDCOLOR "\n");
            }
            else{
                //printf("%s\n", loaded_lab_name);
                play_labyrinth(*loaded_lab, loaded_lab_name);
            }
            menu_choice = MENU;
        }  
        else if(menu_choice == LEADERBOARD){
            Leaderboard* loaded_lb = load_leaderboard();
            if(loaded_lb == NULL){
                printf(RED_HIGHLIGHT "Fichier non trouvé ou corrompu" ENDCOLOR "\n");
            }
            else{
                display_lb(*loaded_lb);
            }
            menu_choice = MENU;
            free(loaded_lb);
        }    
    }while (menu_choice != QUIT);
    free(loaded_lab);
}

Labyrinth* create_and_save(){
    int row;
    int column;
    char name[NAME_SIZE];
    int difficulty;

    ask_lab_size(&row, &column);
    ask_lab_name(NAME_SIZE, name);
    ask_difficulty(&difficulty);

    Labyrinth* lab = init_labyrinth(row, column);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab, difficulty);

    save_into_file(*lab, name);

    display_game_square(*lab); 

    return lab;
}

int play_labyrinth(Labyrinth loaded_lab, const char* lab_name){
    Labyrinth* lab_copy = copy_labyrinth(loaded_lab);
    //initial player position
    int player_row = STARTING_ROW;
    int player_column = STARTING_COLUMN;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int score = DEFAULT_SCORE;
    int won = 0;
    int found_key = 0;
    int ch = UP;
    do {
        int next_x = player_column;
        int next_y = player_row;

        if(!won){ //player can move
            switch (ch) {
                case UP: next_y--; break;
                case DOWN: next_y++; break;
                case LEFT: next_x--; break;
                case RIGHT: next_x++; break;
            }

            //TODO move monsters

            won = check_collision(lab_copy, next_y, next_x, &player_row, &player_column, &score, &found_key);
        }
        if(won){ //won can change value in previous if
            clear();
            //TODO display_win (en mode ncurses)
            mvprintw(0,0,"Vous avez gagné. Veuillez appuyer sur ESC pour continuer");
        }

    } while ((ch = getch()) != ESCAPE); 
    endwin();
    system("clear");
    Leaderboard* lb = load_lb_from_file(lab_name);
    char name[NAME_SIZE];

    if(won){ //TODO need test
        if(score > get_lowest_score(*lb)){
            ask_player_name(NAME_SIZE, name);
            add_player(lb, lab_name, name, score);
        }
        display_lb(*lb);
    }
    return 1;
}

int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key){ //TODO struct game_state ?
    int next_cell = get_cell(*lab, next_y, next_x);  
    if (next_cell != WALL && next_cell != UNDEFINED && next_cell != CLOSED_EXIT) { //can move
        *player_row = next_y;
        *player_column = next_x;

        *score -= MOVING_COST;

        switch (next_cell){
        case KEY:
            *found_key = 1;
            set_cell(lab, next_y, next_x, PATH);
            set_cell(lab, lab->longueur -1 , lab->largeur - 2, EXIT);
            break;
        case BONUS_CELL:
            *score += BONUS;
            set_cell(lab, next_y, next_x, PATH);
            break;
        case TRAP_CELL:
            *score += MALUS;
            set_cell(lab, next_y, next_x, PATH);
            break;
        default:
            break;
        }
        //get si monstre -> score perdu
        //TODO for each de la liste de monstre
            //si current pos = *player_row ,*player_column;
            //perdre le nb de score de son malus
    }
    ncurses_display_game_state(*lab, *player_column, *player_row, *score);

    if(next_cell == EXIT && *found_key){
        return 1; //won
    }
    return 0; //no event
}