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
        empty_buffer();

        if(menu_choice == CREATE){
            loaded_lab = create_and_save(NAME_SIZE, loaded_lab_name);
            menu_choice = MENU;
        }
        else if(menu_choice == LOAD){
            loaded_lab = load_lab(loaded_lab_name); //TODO  propose a list of registered labs (the *.cfg files)
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
                display_leaderboard(*loaded_lb);
            }
            menu_choice = MENU;
            free(loaded_lb);
        }    
    }while (menu_choice != QUIT);
    free(loaded_lab);
}

Labyrinth* create_and_save(int size, char name[size]){
    int row;
    int column;
    int difficulty;

    ask_lab_size(&row, &column);
    ask_lab_name(size, name);
    ask_difficulty(&difficulty);

    Labyrinth* lab = init_labyrinth(row, column);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab, difficulty);

    save_into_file(*lab, name);

    Leaderboard* lb = init_leaderboard();
    save_leaderboard(*lb, name);
    destroy_leaderboard(lb);

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

        if(!won && is_a_movement(ch)){ //player can move
            switch (ch) {
                case UP: 
                case UP_U: next_y--; break;
                case DOWN: 
                case DOWN_U: next_y++; break;
                case LEFT: 
                case LEFT_U: next_x--; break;
                case RIGHT: 
                case RIGHT_U: next_x++; break;
            }

            move_monsters(lab_copy);

            won = check_collision(lab_copy, next_y, next_x, &player_row, &player_column, &score, &found_key);
        }    
        ncurses_display_game_state(*lab_copy, player_column, player_row, score);

        if(won){ //won can change value in previous if
            clear();
            display_win();
        }

    } while ((ch = getch()) != ESCAPE); 
    endwin();
    system("clear");

    Leaderboard* lb = load_lb_from_file(lab_name);
    if(lb == NULL){
        printf(RED_HIGHLIGHT "Un problème s'est produit avec le classement." ENDCOLOR "\n");
    }
    else{
        char name[NAME_SIZE];

        if(won){
            if(lb->nb_of_scores < 10 || score > get_lowest_score(*lb)){
                display_highscore_message();
                ask_player_name(NAME_SIZE, name);
                add_player(lb, lab_name, name, score);
            }
            display_leaderboard(*lb);
        }
    }
    return 1;
}

int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key){ //TODO create a struct game_state
    int next_cell = get_cell(*lab, next_y, next_x); 
    if(next_y != *player_row || next_x != *player_column){ //position changed 
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
        }
    }
    //collisions with monsters
    for(int k = 0; k < lab->n_monsters; k++){
        Monster mon = lab->monsters[k]; 
        if(mon.current_row == *player_row && mon.current_column == *player_column){ //collision
            *score += mon.penalty;
        }
    }
    if(next_cell == EXIT){
        return 1; //won
    }
    return 0; //no event
}

int is_a_movement(int value) {
    switch (value) {
        case UP: 
        case UP_U:
        case DOWN: 
        case DOWN_U:
        case LEFT: 
        case LEFT_U:
        case RIGHT: 
        case RIGHT_U:
            return 1; //value is in enum
        default:
            return 0;
    }
}