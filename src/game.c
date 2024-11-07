#include "game.h"
#include "display.h"
#include "labyrinth.h"
#include "labyrinth_creation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handle_game(){
    int menu_choice = 0;
    Labyrinth* loaded_lab = NULL;
    do{
        display_menu();
        scanf("%d", &menu_choice);
        while (getchar() != '\n');

        if(menu_choice == CREATE){
            //créer un labyrith (avec ou sans affichage)
            printf("creation\n");
            create_and_save();
            //TODO load automatique le labyrinth qui vient d'être créé
        }
        else if(menu_choice == LOAD){
            //Charger lab enregistré
            printf("charger\n");
            loaded_lab = load_lab(); //TODO proposer une liste des lab enregistré (les *.cfg)
            display_game_square(*loaded_lab);
        }
        else if(menu_choice == PLAY){
            //Jouer
            printf("jouer\n");
            if(loaded_lab == NULL){
                printf("Veuillez charger un labyrinth d'abbord\n");
            }
            else{
                printf("jeu\n");
                //display lab with player
                //listen to input with ncurses
                //check collision + déplacer joueur
            }
        }        
    }while (menu_choice != QUIT);
    free(loaded_lab);
}

void save_into_file(Labyrinth lab, const char* filename){ //TODO mettre dans le bon fichier .c
    FILE * file = fopen(filename, "w"); //TODO ajouter le .cfg ?

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

void create_and_save(){
    int row;
    int column;
    char name[NAME_SIZE];

    ask_lab_size(&row, &column);
    printf("row : %d, column : %d", row, column);
    ask_lab_name(NAME_SIZE, name);

    Labyrinth* lab = init_labyrinth(row, column);
    init_unformed_labyrinth(lab);

    init_create_recursive_labyrinth_path(lab);

    save_into_file(*lab, name);

    display_game_square(*lab); 
    
    destroy_labyrinth(lab);
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
        //TODO demander le nom proprement
        scanf("%s", name);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = (int)strlen(name) > 0 && (int)strlen(name) < size ? 1 : 0;
        if(!entreeValide) printf("\033[0;37mEntrée invalide (doit être impair)\033[0;31m\n");
    }
}