#ifndef DISPLAY_H
#define DISPLAY_H
#include "labyrinth.h"
#include "curses.h"

#define GREEN "\033[0;38;5;82m"
#define BLUE "\033[0;38;5;39m"
#define YELLOW "\033[0;38;5;178m"
#define CYAN "\033[0;38;5;85m"
#define ORANGE "\033[0;38;5;208m"

#define WHITE_HIGHLIGHT "\033[0;47m"
#define BLUE_HIGHLIGHT "\033[0;44m"
#define YELLOW_HIGHLIGHT "\033[48;5;220m"
#define RED_HIGHLIGHT "\033[48;5;203m"
#define GREEN_HIGHLIGHT "\033[48;5;28m"
#define DARK_CYAN_HIGHLIGHT "\033[48;5;23m"
#define DARK_RED_HIGHLIGHT "\033[48;5;52m"

#define BOLD "\033[1m"
#define ENDCOLOR "\033[0m"

//ncurses colors
#define PLAYER_PAIR 1
#define WALL_PAIR 2
#define EXIT_PAIR 3
#define KEY_PAIR 4
#define BONUS_PAIR 5
#define TRAP_PAIR 6
#define GHOST_PAIR 7
#define TROLL_PAIR 8
#define WIN_PAIR 9

#define COLOR_DARK_RED COLOR_WHITE+1
#define COLOR_DARK_CYAN COLOR_WHITE+2
#define COLOR_ORANGE COLOR_WHITE+3

//TODO modifier tous les display pour qu'elles prennent en compte l'array de monstre

void display_game(Labyrinth lab);

void display_game_square(Labyrinth lab);

void display_game_with_player(Labyrinth lab, int column, int row, int wait);

void ncurses_display_game_state(Labyrinth lab, int column, int row, int score);

void display_menu();

void display_win();

void display_highscore_message();

void display_leaderboard(Leaderboard lb);

void display_GUI(int score);

#endif