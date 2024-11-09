#include "game.h"
#include "display.h"
#include "labyrinth.h"
#include "labyrinth_creation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void handle_game(){
    int menu_choice = 0;
    Labyrinth* loaded_lab = NULL;
    do{
        display_menu();
        scanf("%d", &menu_choice);
        while (getchar() != '\n');

        if(menu_choice == CREATE){
            loaded_lab = create_and_save();
            menu_choice = MENU;
        }
        else if(menu_choice == LOAD){
            loaded_lab = load_lab(); //TODO proposer une liste des lab enregistré (les *.cfg)
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
                play_labyrinth(*loaded_lab);
            }
            menu_choice = MENU;
        }  
        else if(menu_choice == LEADERBOARD){
            //(demande quel fichier puis display)
        }    
    }while (menu_choice != QUIT);
    free(loaded_lab);
}

void save_into_file(Labyrinth lab, const char* filename){ //TODO mettre dans le bon fichier .c
    FILE * file = fopen(filename, "w"); //TODO ajouter le .cfg

    fprintf(file, "%d %d\n", lab.longueur, lab.largeur);
    fprintf(file, "%s\n", filename);
    for (int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){
            fprintf(file, "%d ", get_cell(lab, i, j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

Labyrinth* load_lab(){
    char name[NAME_SIZE];

    ask_lab_name(NAME_SIZE, name);
    return load_from_file(name);
}

Labyrinth* load_from_file(const char* filename){ //TODO mettre dans le bon fichier .c //TODO erreur si fichier corrompu
    FILE * file = fopen(filename, "r");
    int longueur;
    int largeur;
    char nom[NAME_SIZE];
    int value;

    if(file == NULL)return NULL;

    fscanf(file, "%d %d\n", &longueur, &largeur);
    Labyrinth* lab = init_labyrinth(longueur, largeur);
    if(lab == NULL){ //row or column is even, file is corrupted
        return NULL;
    }

    fscanf(file, "%s\n", nom);
    for (int i = 0; i < longueur; i++){
        for (int j = 0; j < largeur; j++){
            fscanf(file, "%d", &value);
            set_cell(lab, i, j, value);
        }
    }
    fclose(file);
    return lab;
}

Labyrinth* create_and_save(){
    int row;
    int column;
    char name[NAME_SIZE];

    ask_lab_size(&row, &column);
    ask_lab_name(NAME_SIZE, name);

    Labyrinth* lab = init_labyrinth(row, column);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab);

    save_into_file(*lab, name);

    display_game_square(*lab); 

    return lab;
}

void ask_lab_size(int* row, int* column){
    int entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mHauteur du labyrinth : \033[0;37m");
        scanf("%i", row);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = *row%2 == 1 ? 1 : 0;
        if(!entreeValide) printf(RED_HIGHLIGHT "Entrée invalide (doit être impair)" ENDCOLOR "\n");
    }
    entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mLargeur du labyrinth : \033[0;37m");
        scanf("%i", column);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = *column%2 == 1 ? 1 : 0;
        if(!entreeValide) printf(RED_HIGHLIGHT "Entrée invalide (doit être impair)"  ENDCOLOR "\n");
    }
}

void ask_lab_name(int size, char name[size]){
    int entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mNom du labyrinth : \033[0;37m");
        scanf("%s", name);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = (int)strlen(name) > 0 && (int)strlen(name) < size ? 1 : 0;
        if(!entreeValide) printf(RED_HIGHLIGHT "Entrée invalide\n" ENDCOLOR);
    }
}

int play_labyrinth(Labyrinth loaded_lab){
    Labyrinth* lab_copy = copy_labyrinth(loaded_lab);
    //initial player position //TODO write "get player position" function
    int player_row = 0;
    int player_column = 1;

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
            won = check_collision(lab_copy, next_y, next_x, &player_row, &player_column, &score, &found_key);

            //TODO move monsters
        }
        if(won){ //won can change value in previous if
            clear();
            mvprintw(0,0,"Vous avez gagné. Veuillez appuyer sur ESC pour continuer");
        }

    } while ((ch = getch()) != ESCAPE); 
    endwin();
    //TODO check score pour faire le leaderboard (demande prénom + enregistrer dans fichier)
    return 1;
}

int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key){ //TODO struct game_state ?
    int next_cell = get_cell(*lab, next_y, next_x);  
    if (next_cell != WALL && next_cell != UNDEFINED && !(next_cell == EXIT && !*found_key)) { //can move
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
    }
    ncurses_display_game_state(*lab, *player_column, *player_row, *score);

    if(next_cell == EXIT && *found_key){
        return 1; //won
    }
    return 0; //no event
}