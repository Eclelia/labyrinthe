#ifndef GAME_H
#define GAME_H
#include "labyrinth.h"

#define DEFAULT_SCORE 1000 
#define BONUS 50
#define MALUS -50
#define MOVING_COST 10

typedef enum{
    UP = 'z',
    DOWN = 's',
    LEFT = 'q',
    RIGHT = 'd',
    UP_U = 'Z',
    DOWN_U = 'S',
    LEFT_U = 'Q',
    RIGHT_U = 'D',
    ESCAPE = 27,
} Movement;

typedef enum{
    MENU,
    CREATE,
    LOAD,
    PLAY,
    LEADERBOARD,
    QUIT,
} GameOption;

//affiche menu principale + appelle fonction liée aux options
void handle_game();

Labyrinth* create_and_save();

int play_labyrinth(Labyrinth loaded_lab, const char* lab_name);

int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key);

int is_a_movement(int value);

#endif