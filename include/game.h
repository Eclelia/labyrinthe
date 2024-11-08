#ifndef GAME_H
#define GAME_H
#include "labyrinth.h"

#define NAME_SIZE 255 //UNIX max authorized size for filename
#define DEFAULT_SCORE 1000 
#define BONUS 50
#define MALUS -50
#define MOVING_COST 10

typedef enum{
    MENU,
    CREATE,
    LOAD,
    PLAY,
    QUIT
} GameOption;

//affiche menu principale + appelle fonction liée aux options
void handle_game();

void create_and_save();

void ask_lab_size(int* row, int* column);

void ask_lab_name(int size, char name[size]);

Labyrinth* load_lab();

Labyrinth* load_from_file(const char* filename);

#endif