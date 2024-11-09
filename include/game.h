#ifndef GAME_H
#define GAME_H
#include "labyrinth.h"

#define NAME_SIZE 255 //UNIX max authorized size for filename
#define DEFAULT_SCORE 1000 
#define BONUS 50
#define MALUS -50
#define MOVING_COST 10

typedef enum{
    UP = 'z',
    DOWN = 's',
    LEFT = 'q',
    RIGHT = 'd',
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

void ask_lab_size(int* row, int* column);

void ask_lab_name(int size, char name[size]);

Labyrinth* load_lab();

Labyrinth* load_from_file(const char* filename);

int play_labyrinth(Labyrinth loaded_lab);

int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key);

#endif