#ifndef DISPLAY_H
#define DISPLAY_H
#include "labyrinth.h"

#define ORANGE "\033[0;38;5;178m"
#define GREEN "\033[0;38;5;82m"
#define BLUE "\033[0;38;5;39m"
#define YELLOW "\033[0;38;5;220m"
#define WHITE_HIGHLIGHT "\033[0;47m"
#define BLUE_HIGHLIGHT "\033[0;44m"
#define YELLOW_HIGHLIGHT "\033[48;5;220m"
#define RED_HIGHLIGHT "\033[48;5;203m"
#define GREEN_HIGHLIGHT "\033[48;5;28m"

#define BOLD "\033[1m"
#define ENDCOLOR "\033[0m"

//ncurses colors
#define PLAYER_PAIR 1
#define WALL_PAIR 2
#define EXIT_PAIR 3
#define KEY_PAIR 4
#define BONUS_PAIR 5
#define TRAP_PAIR 6

void display_game(Labyrinth lab);

void display_game_square(Labyrinth lab);

void display_game_with_player(Labyrinth lab, int column, int row, int wait);

void ncurses_display_game_state(Labyrinth lab, int column, int row, int score);

void display_menu();

#endif