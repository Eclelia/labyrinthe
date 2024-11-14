/**
 * @file game.h
 * @brief Handles the main gameplay, including menu navigation, labyrinth creation/loading, 
 * and game interactions such as player movement, scoring, and monster handling.
 */

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

/**
 * @brief Main game handler for displaying the menu and processing user inputs to create, load, or play a labyrinth.
 * 
 * This function displays the main menu and lets the player choose between creating a new labyrinth, 
 * loading an existing one, playing a loaded labyrinth, or viewing the leaderboard.
 * 
 * @return void
 */
void handle_game();

/**
 * @brief Creates a labyrinth based on user-specified size and difficulty, then saves it to a file.
 * 
 * This function initializes a labyrinth based on player-defined size and difficulty settings, then saves it.
 * A leaderboard file is created for the new labyrinth. Displays the labyrinth in a square format upon creation.
 * 
 * @param size The maximum length of the labyrinth name.
 * @param name A character array to store the name of the labyrinth.
 * 
 * @return A pointer to the created labyrinth structure.
 */
Labyrinth* create_and_save(int size, char name[size]);

/**
 * @brief Starts the gameplay for a loaded labyrinth.
 * 
 * Initializes the labyrinth gameplay, displaying the labyrinth and allowing the player to move through it
 * while avoiding or interacting with monsters. Manages the game score, winning conditions, and collision events.
 * 
 * @param loaded_lab The labyrinth structure to play.
 * @param lab_name The name of the loaded labyrinth.
 * 
 * @return 1 if the session completes successfully.
 */
int play_labyrinth(Labyrinth loaded_lab, const char* lab_name);

/**
 * @brief Checks player movement for collisions with labyrinth walls, monsters, and special cells.
 * 
 * Updates player coordinates if movement is valid and adjusts the score depending on the cells encountered (traps, bonuses, etc).
 * Handles key retrieval to unlock the labyrinth exit. Also verifies if the player has collided with any monsters and applies penalties.
 * 
 * @param lab Pointer to the labyrinth structure.
 * @param next_y The y-coordinate for the intended player movement.
 * @param next_x The x-coordinate for the intended player movement.
 * @param player_row Pointer to the current player's y-coordinate.
 * @param player_column Pointer to the current player's x-coordinate.
 * @param score Pointer to the player's current score.
 * @param found_key Pointer indicating whether the player has found the key.
 * 
 * @return 1 if the player has won the game by reaching the exit with the key, 0 otherwise.
 */
int check_collision(Labyrinth* lab, int next_y, int next_x, int* player_row, int* player_column, int* score, int* found_key);

/**
 * @brief Verifies if a given input corresponds to a valid player movement command.
 * 
 * Checks if the input value matches any of the movement keys (up, down, left, right or escape).
 * 
 * @param value The input key value to verify.
 * 
 * @return 1 if the value is a movement command, 0 otherwise.
 */
int is_a_movement(int value);

#endif