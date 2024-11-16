/**
 * @file display.h
 * @brief Display functions for the labyrinth game interface.
 *
 * This file contains functions for displaying the labyrinth and game elements
 * on the terminal. Some functions require the terminal to be in "ncurses" mode.
 */

#ifndef DISPLAY_H
#define DISPLAY_H
#include "labyrinth.h"
#include "curses.h"

//terminal colors
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

/**
 * @brief Displays the current state of the labyrinth.
 * 
 * This function iterates through each cell in the labyrinth and prints
 * corresponding symbols based on the cell content (walls, entry, exit, etc.).
 * It uses specific colors and formatting for certain elements like keys and
 * bonus cells.
 * 
 * @param lab The labyrinth structure containing current game layout.
 * 
 * @note This function doesn't display the monsters in the labyrinth.
 */
void display_game(Labyrinth lab);

/**
 * @brief Displays the labyrinth as a grid of uniform cells.
 * 
 * This function renders the labyrinth with a square-shaped representation for each cell type, focusing on the basic layout.
 * It displays all cell types, including walls, entry, exit, and keys, but without the monsters.
 * 
 * @param lab The labyrinth structure containing the current game layout.
 * 
 * @note This function doesn't display the monsters in the labyrinth.
 */
void display_game_square(Labyrinth lab);

/**
 * @brief Displays the labyrinth with the player's current position.
 * 
 * This function displays the labyrinth with a visual indication of the player's position, highlighted in blue.
 * It displays all cell types, including walls, entry, exit, and keys, but without the monsters.
 * The function optionally waits for a short delay and clears the screen afterward.
 * 
 * @param lab The labyrinth structure containing the current game layout.
 * @param column The player's column position.
 * @param row The player's row position.
 * @param wait If true, a brief delay is added before clearing the screen.
 * 
 * @note This function doesn't display the monsters in the labyrinth.
 */
void display_game_with_player(Labyrinth lab, int column, int row, int wait);

/**
 * @brief Displays the game state in ncurses mode, including player position, monsters, score and GUI.
 * 
 * This function uses ncurses to render the labyrinth, following the player's position.
 * It accounts for monsters in the `lab` structure's array and highlights them based on type.
 * Additional GUI elements, such as the player’s score and controls, are displayed at the bottom.
 * 
 * @param lab The labyrinth structure containing the current game layout, including monsters.
 * @param column The player's column position.
 * @param row The player's row position.
 * @param score The player's current score.
 * 
 * @note This function requires the terminal to be in "ncurses" mode and also supports the array of monsters in the labyrinth.
 */
void ncurses_display_game_state(Labyrinth lab, int column, int row, int score);

/**
 * @brief Displays the main menu in a stylized ASCII art format.
 * 
 * Presents the main menu options, including options for creating or loading a labyrinth, playing the game, viewing the leaderboard, and quitting.
 */
void display_menu();

/**
 * @brief Displays a victory message in ncurses mode.
 * 
 * Shows a celebratory win message in the top corner of the screen. This function requires ncurses for formatted display.
 * 
 * @note This function requires the terminal to be in "ncurses" mode.
 */
void display_win();

/**
 * @brief Displays a high score animation on the terminal.
 * 
 * Uses a color animation to display a congratulatory message for new high scores.
 */
void display_highscore_message();

/**
 * @brief Displays the leaderboard in a table format.
 * 
 * This function prints out the leaderboard entries, showing the rank, player names, and scores.
 * 
 * @param lb The leaderboard structure containing players' scores.
 */
void display_leaderboard(Leaderboard lb);

/**
 * @brief Displays the game GUI in ncurses mode, showing score, controls, and the various cell types of the game.
 * 
 * This function provides an in-game GUI at the bottom of the screen, displaying information about controls, 
 * score, and explanations for various labyrinth cell types, such as the exit and trap cells.
 * 
 * @param score The player's current score.
 * 
 * @note This function requires the terminal to be in "ncurses" mode.
 */
void display_GUI(int score);

/**
 * @brief Initializes custom colors and color pairs for ncurses display.
 * 
 * Sets up color pairs and custom color configurations for various game elements, including the player, walls, exit,
 * monsters, and traps.
 * 
 * @note This function requires the terminal to be in "ncurses" mode.
 */
void init_ncurses_colors();

#endif