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
        }
        else if(menu_choice == LOAD){
            loaded_lab = load_lab(); //TODO proposer une liste des lab enregistré (les *.cfg)
            if(loaded_lab == NULL){
                printf("Fichier non trouvé\n");
            }
            else{
                display_game_square(*loaded_lab);
            }
        }
        else if(menu_choice == PLAY){
            if(loaded_lab == NULL){
                printf("Veuillez d'abord charger un labyrinthe\n");
            }
            else{
                play_labyrinth(loaded_lab);
            }
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

Labyrinth* load_from_file(const char* filename){ //TODO mettre dans le bon fichier .c
    FILE * file = fopen(filename, "r");
    int longueur;
    int largeur;
    char nom[NAME_SIZE];
    int value;

    if(file == NULL)return NULL;

    fscanf(file, "%d %d\n", &longueur, &largeur);
    Labyrinth* lab = init_labyrinth(longueur, largeur);

    fscanf(file, "%s\n", nom);
    for (int i = 0; i < longueur; i++){
        for (int j = 0; j < largeur; j++){
            fscanf(file, "%d", &value);
            set_cell(lab, i, j, value);
        }
        fprintf(file, "\n");
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
        if(!entreeValide) printf("\033[0;37mEntrée invalide (doit être impair)\033[0;31m\n");
    }
    entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mLargeur du labyrinth : \033[0;37m");
        scanf("%i", column);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = *column%2 == 1 ? 1 : 0;
        if(!entreeValide) printf("\033[0;37mEntrée invalide (doit être impair)\033[0;31m\n");
    }
}

void ask_lab_name(int size, char name[size]){
    int entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mNom du labyrinth : \033[0;37m");
        scanf("%s", name);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = (int)strlen(name) > 0 && (int)strlen(name) < size ? 1 : 0;
        if(!entreeValide) printf("\033[0;37mEntrée invalide (doit être impair)\033[0;31m\n");
    }
}

int play_labyrinth(Labyrinth* loaded_lab){
    //TODO init src en dehors de la methode pour message de réussite dans une window
    //TODO refactor en plusieurs plus petite méthode
    //initial player position
    //TODO write "get player position" function
    int player_row = 0;
    int player_column = 1;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int ch = UP;
    do {
        int next_x = player_column;
        int next_y = player_row;

        switch (ch) {
            case UP: next_y--; break;
            case DOWN: next_y++; break;
            case LEFT: next_x--; break;
            case RIGHT: next_x++; break;
        }

        //TODO check les autres collisions (switch ?)
        int next_cell = get_cell(*loaded_lab, next_y, next_x);  
        if (next_cell != WALL && next_cell != UNDEFINED) { //can move
            player_row = next_y;
            player_column = next_x;
            //on bouge donc score perdu

            //get si monstre -> score perdu
            //si piège -> score perdu
            //si bonus -> score gagné
        }
        ncurses_display_game_with_player(*loaded_lab, player_column, player_row);

        if(next_cell == EXIT){
            clear();
            mvprintw(0,0,"Vous avez gagné. Veuillez appuyer sur ESC pour continuer"); //TODO empêcher le joueur de remonter (flag ?)
        }
    } while ((ch = getch()) != ESCAPE); 
    endwin();
    return 1;
}