#ifndef DISPLAY_H
#define DISPLAY_H
#include "labyrinth.h"

#define ORANGE "\033[0;38;5;178m"
#define GREEN "\033[0;38;5;82m"
#define BLUE "\033[0;38;5;39m"
#define WHITE_HIGHLIGHT "\033[0;47m"
#define BLUE_HIGHLIGHT "\033[0;44m"
#define BOLD "\033[1m"
#define ENDCOLOR "\033[0m"

//ncurses colors
#define PLAYER_PAIR 1
#define WALL_PAIR 2
#define EXIT_PAIR 3

void display_game(Labyrinth lab);

void display_game_square(Labyrinth lab);

void display_game_with_player(Labyrinth lab, int column, int row, int wait);

void ncurses_display_game_with_player(Labyrinth lab, int column, int row);

void display_menu();

#endif