/**
 * @file test_labyrinth.c
 * @brief Testing the functions of the project
 * @author Célia Dennetiere
 */

#include "minunit.h"
#include "display.h"
#include "game.h"
#include "game_struct.h"
#include "labyrinth_creation.h"
#include "labyrinth_file_helper.h"
#include "labyrinth.h"
#include "leaderboard.h"
#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void test_setup(void) {
}

void test_teardown(void) {
}

MU_TEST(check_collision_with_key){
    printf("Testing collision with key\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 7;
    int player_column = 2;
    int found_key = 0;

    mu_assert_int_eq(CLOSED_EXIT, get_cell(*lab, lab->longueur -1 , lab->largeur - 2));

    int res = check_collision(lab, 7, 3, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(3, player_column);
    mu_assert_int_eq(DEFAULT_SCORE-MOVING_COST, score);
    mu_assert_int_eq(1, found_key);
    mu_assert_int_eq(PATH, get_cell(*lab, 7, 3));
    mu_assert_int_eq(EXIT, get_cell(*lab, lab->longueur -1 , lab->largeur - 2));

}
MU_TEST(check_collision_with_bonus){
    printf("Testing collision with bonus\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 3;
    int player_column = 4;
    int found_key = 0;

    int res = check_collision(lab, 3, 5, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(5, player_column);
    mu_assert_int_eq(PATH, get_cell(*lab, 3, 5));
    mu_assert_int_eq(DEFAULT_SCORE+BONUS-MOVING_COST, score);
}
MU_TEST(check_collision_with_malus){
    printf("Testing collision with malus\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 1;
    int player_column = 4;
    int found_key = 0;

    int res = check_collision(lab, 1, 5, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(5, player_column);
    mu_assert_int_eq(PATH, get_cell(*lab, 1, 5));
    mu_assert_int_eq(DEFAULT_SCORE+MALUS-MOVING_COST, score);
}
MU_TEST(check_collision_with_monster){
    printf("Testing collision with monsters\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 2;
    int player_column = 1;
    int found_key = 0;

    int res = check_collision(lab, 1, 1, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(1, player_row);
    mu_assert_int_eq(DEFAULT_SCORE-MOVING_COST+TROLL_P, score);

    res = check_collision(lab, 1, 2, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(2, player_column);
    mu_assert_int_eq(980-MOVING_COST+GHOST_P, score);
}
MU_TEST(check_collision_with_exit){
    printf("Testing collision with exit\n");
    Labyrinth* lab = load_from_file("test_open_lab");
    int score = DEFAULT_SCORE;
    int player_row = 7;
    int player_column = 7;
    int found_key = 0;

    int res = check_collision(lab, 8, 7, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(1, res);
}
MU_TEST(check_collision_with_closed_exit){
    printf("Testing collision with closed exit\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 7;
    int player_column = 7;
    int found_key = 0;

    int res = check_collision(lab, 8, 7, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(7, player_row);
}
MU_TEST(check_collision_with_wall){
    printf("Testing collision with wall\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 2;
    int player_column = 1;
    int found_key = 0;

    int res = check_collision(lab, 2, 2, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(2, player_row);
    mu_assert_int_eq(1, player_column);
}
MU_TEST(check_collision_with_nothing){
    printf("Testing collision with nothing\n");
    Labyrinth* lab = load_from_file("test_lab");
    int score = DEFAULT_SCORE;
    int player_row = 7;
    int player_column = 1;
    int found_key = 0;

    int res = check_collision(lab, 6, 1, &player_row, &player_column, &score, &found_key);

    mu_assert_int_eq(0, res);
    mu_assert_int_eq(6, player_row);
    mu_assert_int_eq(1, player_column);
}

MU_TEST(init_lab_with_small_size){
    printf("Testing create with size 3x1\n");
    mu_check(init_labyrinth(3,1) == NULL);
    printf(" -- passed\n");
}
MU_TEST(init_lab_with_even_column){
    printf("Testing create with size 3x1\n");
    mu_check(init_labyrinth(9,10) == NULL);
    printf(" -- passed\n");
}
MU_TEST(init_lab_with_even_row){
    printf("Testing create with size 3x1\n");
    mu_check(init_labyrinth(10,9) == NULL);
    printf(" -- passed\n");
}
MU_TEST(init_lab_with_no_problem){
    printf("Testing create with size 3x1\n");
    mu_check(init_labyrinth(9,11) != NULL);
    printf(" -- passed\n");
}
MU_TEST(get_all_neighbours){
    printf("Testing getting all 4 neighbours\n");
    Labyrinth* lab = load_from_file("test_lab");
    Lab_cell neighbours[4];
    int res = get_possible_neighbours(*lab, 3, 3, neighbours);

    mu_assert_int_eq(4, res);
}
MU_TEST(get_no_neighbours){
    printf("Testing getting no neighbours\n");
    Labyrinth* lab = load_from_file("test_lab");
    Lab_cell neighbours[4];
    int res = get_possible_neighbours(*lab, -3, -3, neighbours);

    mu_assert_int_eq(0, res);
}
MU_TEST(get_some_neighbours){
    printf("Testing getting some neighbours\n");
    Labyrinth* lab = load_from_file("test_lab");
    Lab_cell neighbours[4];
    int res = get_possible_neighbours(*lab, 1, 7, neighbours);

    mu_assert_int_eq(2, res);
}
MU_TEST(test_make_lab_playable){
    printf("Testing making lab playable\n");
    Labyrinth* lab = load_from_file("test_unfinished_lab");
    
    make_labyrinth_playable(lab);

    mu_assert_int_eq(ENTRY, get_cell(*lab, STARTING_ROW, STARTING_COLUMN));
    mu_assert_int_eq(EXIT, get_cell(*lab, lab->longueur -1 , lab->largeur - 2));    
}
MU_TEST(test_add_key_and_lock_door){
    printf("Testing locking the door\n");
    Labyrinth* lab = load_from_file("test_unfinished_lab");
    
    add_key_and_lock_door(lab);

    mu_assert_int_eq(CLOSED_EXIT, get_cell(*lab, lab->longueur -1 , lab->largeur - 2));
}
MU_TEST(test_copy_labyrinth){
    printf("Testing copying lab\n");
    Labyrinth* lab = load_from_file("test_lab");

    Labyrinth* lab_copy = copy_labyrinth(*lab);

    mu_assert_int_eq(9, lab_copy->longueur); 
    mu_assert_int_eq(9, lab_copy->largeur);
    mu_assert_int_eq(2, lab_copy->n_monsters);
    for (int i = 0; i < lab->longueur; i++){
        for (int j = 0; j < lab->largeur; j++){
            mu_assert_int_eq(get_cell(*lab, i, j), get_cell(*lab_copy, i, j));
        }
    }
    for(int i = 0; i < lab->n_monsters; i++){
        mu_assert_int_eq(lab->monsters[i].row, lab_copy->monsters[i].row);
        mu_assert_int_eq(lab->monsters[i].column, lab_copy->monsters[i].column);
        mu_assert_int_eq(lab->monsters[i].type, lab_copy->monsters[i].type);
        mu_assert_int_eq(lab->monsters[i].penalty, lab_copy->monsters[i].penalty);
    }
}


MU_TEST(test_save_into_file){
    printf("Testing saving lab into file\n");
    char name[14] = {'t','e','s','t','_','s','a','v','e','_','l','a','b','\0'};
    Labyrinth* lab = load_from_file("test_lab");

    save_into_file(*lab, name);

    FILE *f1 = fopen("data/test_lab.cfg", "r");
    if (!f1) { printf("error\n"); };
    FILE *f2 = fopen("data/test_save_lab.cfg", "r");
    if (!f2) { printf("error\n"); };
    
    int samefile = 1;
    int longueur;
    int largeur;
    int longueur2;
    int largeur2;
    char nom[NAME_SIZE];

    fscanf(f1, "%d %d\n", &longueur, &largeur);
    fscanf(f2, "%d %d\n", &longueur2, &largeur2);

    mu_assert_int_eq(longueur, longueur2);
    mu_assert_int_eq(largeur, largeur2);

    fscanf(f1, "%s\n", nom);
    fscanf(f2, "%s\n", nom); //skipping name

    int c1, c2;
    while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) {
        if (c1 != c2) {
            samefile = false;
            break;
        }
    }
    fclose (f1), fclose (f2);

    mu_check(samefile == 1);
}
MU_TEST(test_load_from_file_with_monsters){
    printf("Testing load lab with monsters\n");
    Labyrinth* lab = load_from_file("test_lab");

    mu_assert_int_eq(9, lab->largeur);
    mu_assert_int_eq(9, lab->longueur);
    mu_assert_int_eq(2, lab->n_monsters);

    mu_assert_int_eq(1, lab->monsters[0].row);
    mu_assert_int_eq(2, lab->monsters[0].column);
    mu_assert_int_eq(-7, lab->monsters[0].type);
    mu_assert_int_eq(-10, lab->monsters[0].penalty);
    mu_assert_int_eq(1, lab->monsters[1].row);
    mu_assert_int_eq(1, lab->monsters[1].column);
    mu_assert_int_eq(-8, lab->monsters[1].type);
    mu_assert_int_eq(-10, lab->monsters[1].penalty);
}
MU_TEST(test_load_from_file_without_monsters){
    printf("Testing load lab without monsters\n");
    Labyrinth* lab = load_from_file("test_open_lab");

    mu_assert_int_eq(9, lab->largeur);
    mu_assert_int_eq(9, lab->longueur);
    mu_assert_int_eq(0, lab->n_monsters);
}
MU_TEST(test_load_from_wrong_file){
    printf("Testing load from wring file\n");
    Labyrinth* lab = load_from_file("doesnt_exist");

    mu_check(lab == NULL);
}


MU_TEST(get_wrong_cell){
    printf("Testing get wrong cell\n");
    Labyrinth* lab = load_from_file("test_lab");

    mu_assert_int_eq(UNDEFINED, get_cell(*lab, -1, -1));
    mu_assert_int_eq(UNDEFINED, get_cell(*lab, 10, 0));
    mu_assert_int_eq(UNDEFINED, get_cell(*lab, 0, 10));
}
MU_TEST(test_get_cells){
    printf("Testing get cells\n");
    Labyrinth* lab = load_from_file("test_lab");

    mu_assert_int_eq(WALL, get_cell(*lab, 3, 2));
    mu_assert_int_eq(CLOSED_EXIT, get_cell(*lab, 8, 7));
    mu_assert_int_eq(5, get_cell(*lab, 7, 1));
}
MU_TEST(set_wrong_cell){
    printf("Testing set wrong cell\n");
    Labyrinth* lab = load_from_file("test_lab");

    mu_assert_int_eq(-1, set_cell(lab, -1, -1, PATH));
    mu_assert_int_eq(-1, set_cell(lab, 10, 0, PATH));
    mu_assert_int_eq(-1, set_cell(lab, 0, 10, PATH));
}
MU_TEST(test_set_cell){
    printf("Testing set cells\n");
    Labyrinth* lab = load_from_file("test_lab");

    set_cell(lab, 3, 2, EXIT);
    set_cell(lab, 8, 7, EXIT);
    set_cell(lab, 7, 1, EXIT);

    mu_assert_int_eq(EXIT, get_cell(*lab, 3, 2));
    mu_assert_int_eq(EXIT, get_cell(*lab, 8, 7));
    mu_assert_int_eq(EXIT, get_cell(*lab, 7, 1));
}
MU_TEST(test_get_nb_bonus){
    printf("Testing get nb bonus\n");
    Labyrinth* lab = load_from_file("test_lab");

    mu_assert_int_eq(2, get_nb_bonus(*lab));
}
MU_TEST(test_get_no_bonus){
    printf("Testing get no bonus\n");
    Labyrinth* lab = load_from_file("test_open_lab");

    mu_assert_int_eq(0, get_nb_bonus(*lab));
}
MU_TEST(test_get_nth_bonus){
    printf("Testing get nth bonus\n");
    Labyrinth* lab = load_from_file("test_lab");

    int bonus_row, bonus_column;
    int res = get_nth_bonus(*lab, 2, &bonus_row, &bonus_column);

    mu_assert_int_eq(1, res);
    mu_assert_int_eq(3, bonus_row);
    mu_assert_int_eq(5, bonus_column);

    res = get_nth_bonus(*lab, 54, &bonus_row, &bonus_column);

    mu_assert_int_eq(0, res);
}


MU_TEST(test_init_lb){
    printf("Testing init leaderboard\n");
    Leaderboard* lb = init_leaderboard();
    mu_check(lb != NULL);
}
MU_TEST(test_save_lb){
    printf("Testing save leaderboard\n");
    char name[14] = {'t','e','s','t','_','s','a','v','e','_','l','a','b','\0'};
    Leaderboard* lb = load_lb_from_file("test_lab");

    save_leaderboard(*lb, name);

    FILE *f1 = fopen("data/test_lab.score", "r");
    if (!f1) { printf("error\n"); };
    FILE *f2 = fopen("data/test_save_lab.score", "r");
    if (!f2) { printf("error\n"); };
    
    int samefile = 1;
    int c1, c2;
    while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) {
        if (c1 != c2) {
            samefile = false;
            break;
        }
    }
    fclose (f1), fclose (f2);
    mu_check(samefile == 1);
}
MU_TEST(test_load_lb_from_file){
    printf("Testing load leaderboard\n");
    Leaderboard* lb = load_lb_from_file("test_lab");

    mu_assert_int_eq(4, lb->nb_of_scores);
    mu_assert_string_eq("Audrey", lb->score_list[0].name);
    mu_assert_int_eq(790, lb->score_list[0].score);
    mu_assert_string_eq("Thibaud", lb->score_list[1].name);
    mu_assert_int_eq(790, lb->score_list[1].score);
    mu_assert_string_eq("Jean", lb->score_list[2].name);
    mu_assert_int_eq(790, lb->score_list[2].score);
    mu_assert_string_eq("Celia", lb->score_list[3].name);
    mu_assert_int_eq(780, lb->score_list[3].score);
}
MU_TEST(test_get_lowest_score){
    printf("Testing get lowest score\n");
    Leaderboard* lb = load_lb_from_file("test_lab");

    mu_assert_int_eq(780, get_lowest_score(*lb));
}
MU_TEST(test_get_lowest_score_when_none){
    printf("Testing get lowest score when none\n");
    Leaderboard* lb = load_lb_from_file("test_unfinished_lab");

    mu_assert_int_eq(INT_MIN, get_lowest_score(*lb));
}
MU_TEST(test_add_player_when_not_full){
    printf("Testing set new score\n");
    
    Leaderboard* lb = load_lb_from_file("test_lab");
    add_player(lb, "test_lab", "Charles", 1000);

    mu_assert_int_eq(5, lb->nb_of_scores);
    mu_assert_int_eq(1000, lb->score_list[0].score);
    mu_assert_string_eq("Charles", lb->score_list[0].name);

    //nothing else changed
    mu_assert_string_eq("Audrey", lb->score_list[1].name);
    mu_assert_int_eq(790, lb->score_list[1].score);
    mu_assert_string_eq("Thibaud", lb->score_list[2].name);
    mu_assert_int_eq(790, lb->score_list[2].score);
    mu_assert_string_eq("Jean", lb->score_list[3].name);
    mu_assert_int_eq(790, lb->score_list[3].score);
    mu_assert_string_eq("Celia", lb->score_list[4].name);
    mu_assert_int_eq(780, lb->score_list[4].score);

    //revert changes
    Leaderboard* new_lb = init_leaderboard();
    add_player(new_lb, "test_lab", "Audrey", 790);
    add_player(new_lb, "test_lab", "Thibaud", 790);
    add_player(new_lb, "test_lab", "Jean", 790);
    add_player(new_lb, "test_lab", "Celia", 780);
    save_leaderboard(*new_lb, "test_lab");
}
MU_TEST(test_add_player_when_full){
    printf("Testing set new score when full\n");
    Leaderboard* lb = load_lb_from_file("test_open_lab");
    add_player(lb, "test_open_lab", "Charles", 750);

    mu_assert_int_eq(10, lb->nb_of_scores);
    mu_assert_int_eq(750, lb->score_list[5].score);
    mu_assert_string_eq("Charles", lb->score_list[5].name);

    //nothing else changed
    mu_assert_string_eq("Audrey", lb->score_list[0].name);
    mu_assert_int_eq(790, lb->score_list[0].score);
    mu_assert_string_eq("Thibaud", lb->score_list[1].name);
    mu_assert_int_eq(790, lb->score_list[1].score);
    mu_assert_string_eq("Jean", lb->score_list[2].name);
    mu_assert_int_eq(780, lb->score_list[2].score);
    mu_assert_string_eq("Celia", lb->score_list[3].name);
    mu_assert_int_eq(780, lb->score_list[3].score);
    mu_assert_string_eq("Jean", lb->score_list[4].name);
    mu_assert_int_eq(770, lb->score_list[4].score);

    mu_assert_string_eq("Audrey", lb->score_list[6].name);
    mu_assert_int_eq(700, lb->score_list[6].score);
    mu_assert_string_eq("Thibaud", lb->score_list[7].name);
    mu_assert_int_eq(500, lb->score_list[7].score);
    mu_assert_string_eq("Jean", lb->score_list[8].name);
    mu_assert_int_eq(450, lb->score_list[8].score);
    mu_assert_string_eq("Celia", lb->score_list[9].name);
    mu_assert_int_eq(420, lb->score_list[9].score);

    //revert changes
    Leaderboard* new_lb = init_leaderboard();
    add_player(new_lb, "test_open_lab", "Audrey", 790);
    add_player(new_lb, "test_open_lab", "Thibaud", 790);
    add_player(new_lb, "test_open_lab", "Jean", 780);
    add_player(new_lb, "test_open_lab", "Celia", 780);
    add_player(new_lb, "test_open_lab", "Jean", 770);
    add_player(new_lb, "test_open_lab", "Audrey", 700);
    add_player(new_lb, "test_open_lab", "Thibaud", 500);
    add_player(new_lb, "test_open_lab", "Jean", 450);
    add_player(new_lb, "test_open_lab", "Celia", 420);
    add_player(new_lb, "test_open_lab", "Jean", -100);
    save_leaderboard(*new_lb, "test_open_lab");
}


MU_TEST(test_add_monsters){
    printf("Testing adding monsters\n");
    Labyrinth* lab = load_from_file("test_lab");
    lab->n_monsters = 0;
    lab->monsters = NULL; //reset array

    add_monsters(lab);
    mu_check(lab->n_monsters!=0);
}
MU_TEST(test_add_ghost){
    printf("Testing adding ghost\n");
    Labyrinth* lab = load_from_file("test_lab");
    lab->n_monsters = 0;
    lab->monsters = NULL; //reset array
    lab->monsters = malloc(sizeof(Monster)*2);

    add_ghost(lab);
    mu_assert_int_eq(-7, lab->monsters[0].type);
}
MU_TEST(test_add_troll){
    printf("Testing adding troll\n");
    Labyrinth* lab = load_from_file("test_lab");
    lab->n_monsters = 0;
    lab->monsters = NULL; //reset array
    lab->monsters = malloc(sizeof(Monster)*2);

    add_troll(lab, 2);
    mu_assert_int_eq(-8, lab->monsters[0].type);
}



MU_TEST_SUITE(test_game) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(check_collision_with_key);
    MU_RUN_TEST(check_collision_with_bonus);
    MU_RUN_TEST(check_collision_with_malus);
    MU_RUN_TEST(check_collision_with_monster);
    MU_RUN_TEST(check_collision_with_exit);
    MU_RUN_TEST(check_collision_with_closed_exit);
    MU_RUN_TEST(check_collision_with_wall);
    MU_RUN_TEST(check_collision_with_nothing);
}

MU_TEST_SUITE(test_creation) {
    MU_RUN_TEST(init_lab_with_small_size);
    MU_RUN_TEST(init_lab_with_even_column);
    MU_RUN_TEST(init_lab_with_even_row);
    MU_RUN_TEST(init_lab_with_no_problem);
    MU_RUN_TEST(get_all_neighbours);
    MU_RUN_TEST(get_no_neighbours);
    MU_RUN_TEST(get_some_neighbours);
    MU_RUN_TEST(test_make_lab_playable);
    MU_RUN_TEST(test_add_key_and_lock_door);
    MU_RUN_TEST(test_copy_labyrinth);
}

MU_TEST_SUITE(test_file) {
    MU_RUN_TEST(test_save_into_file);
    MU_RUN_TEST(test_load_from_file_with_monsters);
    MU_RUN_TEST(test_load_from_file_without_monsters);
    MU_RUN_TEST(test_load_from_wrong_file);
}

MU_TEST_SUITE(test_labyrinth_acces) {
    MU_RUN_TEST(get_wrong_cell);
    MU_RUN_TEST(test_get_cells);
    MU_RUN_TEST(set_wrong_cell);
    MU_RUN_TEST(test_set_cell);
    MU_RUN_TEST(test_get_nb_bonus);
    MU_RUN_TEST(test_get_no_bonus);
    MU_RUN_TEST(test_get_nth_bonus);
}

MU_TEST_SUITE(test_leaderboard) {
    MU_RUN_TEST(test_init_lb);
    MU_RUN_TEST(test_save_lb);
    MU_RUN_TEST(test_load_lb_from_file);
    MU_RUN_TEST(test_get_lowest_score);
    MU_RUN_TEST(test_get_lowest_score_when_none);
    MU_RUN_TEST(test_add_player_when_not_full);
    MU_RUN_TEST(test_add_player_when_full);
}

MU_TEST_SUITE(test_monsters) {
    MU_RUN_TEST(test_add_monsters);
    MU_RUN_TEST(test_add_ghost);
    MU_RUN_TEST(test_add_troll);
}

int main() {
    MU_RUN_SUITE(test_game);
    MU_RUN_SUITE(test_creation);
    MU_RUN_SUITE(test_file);
    MU_RUN_SUITE(test_labyrinth_acces);
    MU_RUN_SUITE(test_leaderboard);
    MU_RUN_SUITE(test_monsters);
    MU_REPORT();
    return MU_EXIT_CODE;
}
