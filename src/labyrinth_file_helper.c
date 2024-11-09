#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinth_file_helper.h"
#include "display.h"
#include "labyrinth_creation.h"

void save_into_file(Labyrinth lab, const char* filename){
    size_t total_size = strlen(DATA_PATH) + strlen(filename) + strlen(".cfg") + 1;
    char* dest = malloc(total_size);

    strcpy(dest, DATA_PATH);
    strcat(dest, filename);
    strcat(dest, ".cfg");

    FILE * file = fopen(dest, "w");

    fprintf(file, "%d %d\n", lab.longueur, lab.largeur);
    fprintf(file, "%s\n", filename);
    for (int i = 0; i < lab.longueur; i++){
        for (int j = 0; j < lab.largeur; j++){
            fprintf(file, "%d ", get_cell(lab, i, j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
    free(dest);
}

Labyrinth* load_lab(char* name_out){
    char name[NAME_SIZE];

    ask_lab_name(NAME_SIZE, name);
    strcpy(name_out, name);
    return load_from_file(name);
}

Labyrinth* load_from_file(const char* filename){ //TODO erreur si fichier corrompu
    size_t total_size = strlen(DATA_PATH) + strlen(filename) + strlen(".cfg") + 1;
    char* dest = malloc(total_size);

    strcpy(dest, DATA_PATH);
    strcat(dest, filename);
    strcat(dest, ".cfg");

    FILE * file = fopen(dest, "r");
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