#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "leaderboard.h"
#include "labyrinth_creation.h"
#include "labyrinth_file_helper.h"
#include "display.h"

Leaderboard* init_leaderboard(){
    Leaderboard* new_lb = malloc(sizeof(Leaderboard));
    new_lb->nb_of_scores = 0;
    new_lb->score_list = malloc(10*sizeof(P_score));
    return new_lb;
}

P_score* init_player_score(const char* name, int score){
    P_score* new_pc = malloc(sizeof(P_score));
    new_pc->name = malloc(sizeof(char)*strlen(name));
    strcpy(new_pc->name, name);
    new_pc->score = score;
    return new_pc;
}

void destroy_leaderboard(Leaderboard* lb){
    for(int i = 0; i< lb->nb_of_scores; i++){
        destroy_player_score(&(lb->score_list[i]));
    }
    free(lb->score_list);
    free(lb);
}

void destroy_player_score(P_score* pc){
    free(pc->name);
    free(pc);
}

void save_leaderboard(Leaderboard lb, const char* filename){
    size_t total_size = strlen(DATA_PATH) + strlen(filename) + strlen(".score") + 1;
    char* dest = malloc(total_size);

    strcpy(dest, DATA_PATH);
    strcat(dest, filename);
    strcat(dest, ".score");

    FILE * file = fopen(dest, "w");

    fprintf(file, "%d\n", lb.nb_of_scores);
    for(int i = 0; i < lb.nb_of_scores; i++){
        fprintf(file, "%s\n", lb.score_list[i].name);
        fprintf(file, "%d\n", lb.score_list[i].score);
    }
    fclose(file);
    free(dest);
}

Leaderboard* load_leaderboard(){
    char name[NAME_SIZE];

    ask_lab_name(NAME_SIZE, name);
    return load_lb_from_file(name);
}

Leaderboard* load_lb_from_file(const char* filename){ //TODO erreur si fichier corrompu
    Leaderboard* loaded_lb = malloc(sizeof(Leaderboard));

    size_t total_size = strlen(DATA_PATH) + strlen(filename) + strlen(".score") + 1;
    char* dest = malloc(total_size);
    strcpy(dest, DATA_PATH);
    strcat(dest, filename);
    strcat(dest, ".score");

    FILE * file = fopen(dest, "r");
    if(file == NULL)return NULL;

    fscanf(file, "%d\n", &(loaded_lb->nb_of_scores));
    loaded_lb->score_list = malloc(loaded_lb->nb_of_scores * sizeof(P_score));

    for(int i = 0; i < loaded_lb->nb_of_scores; i++){
        char name[NAME_SIZE];
        fscanf(file, "%s\n", name);

        int score;
        fscanf(file, "%d\n", &score);

        P_score* p_score = init_player_score(name, score);
        loaded_lb->score_list[i] = *p_score;
    }

    fclose(file);
    free(dest);
    return loaded_lb;
}

void display_lb(Leaderboard lb){
    printf("-----LEADERBOARD-----\n");
    for(int i = 0; i < lb.nb_of_scores; i++){
        printf("%2d. Joueur : %20s  Score : %d\n", i+1, lb.score_list[i].name, lb.score_list[i].score);
    }
}

int get_lowest_score(Leaderboard lb){
    return lb.score_list[lb.nb_of_scores - 1].score;
}

void ask_player_name(int size, char name[size]){
    int entreeValide = 0;
    while(!entreeValide){
        printf("\033[0;35mQuel est votre nom ? \033[0;37m");
        scanf("%s", name);
        while ((getchar()) != '\n'); //vider le buffer
        entreeValide = (int)strlen(name) > 0 && (int)strlen(name) < size ? 1 : 0;
        if(!entreeValide) printf(RED_HIGHLIGHT "Entrée invalide\n" ENDCOLOR);
    }
}

 //(en fonction de nb_of_scores et nb_of_score ++ si inf à 10)
 void add_player(Leaderboard* lb, const char* filename, const char* name, int score){
    P_score* p_score = init_player_score(name, score);
    if(lb->nb_of_scores < LEADERBOARD_SIZE){
        lb->score_list[lb->nb_of_scores] = *p_score;
        lb->nb_of_scores++;
    }
    else{
        lb->score_list[LEADERBOARD_SIZE -1] = *p_score;
    }
    sort_player(lb);
    save_leaderboard(*lb, filename);
 }

 int compare_scores(const void *obj_a, const void *obj_b) {
    P_score *player_a = (P_score *)obj_a;
    P_score *player_b = (P_score *)obj_b;
    return player_b->score - player_a->score;
}

 void sort_player(Leaderboard* lb){
    qsort(lb->score_list, lb->nb_of_scores, sizeof(P_score), compare_scores);
 }