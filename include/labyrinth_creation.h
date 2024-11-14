/**
 * @file labyrinth_creation.h
 * @brief Functions for initializing, creating, and modifying labyrinth structures.
 */

#ifndef LABYRINTH_CREATION_H
#define LABYRINTH_CREATION_H
#include "labyrinth.h"

#define RATIO_WALL_TO_BREAK 65
#define RATIO_BONUS 32
#define RATIO_TRAP RATIO_BONUS/2

#define DATA_PATH "data/"

/**
 * @brief Initializes a labyrinth structure with the specified dimensions.
 * 
 * Allocates memory for a labyrinth and checks if its dimensions are valid.
 * 
 * @param row Number of rows for the labyrinth.
 * @param column Number of columns for the labyrinth.
 * 
 * @return A pointer to the initialized labyrinth structure, or NULL if dimensions are invalid.
 */
Labyrinth* init_labyrinth(int row, int column);

/**
 * @brief Sets up an unformed labyrinth with walls and unique cell IDs for later path creation.
 * 
 * Initializes cells to distinguish walls from paths, with unique IDs in potential path cells.
 * 
 * @param labyrinth Pointer to the labyrinth structure to initialize.
 * 
 * @return void
 */
void init_unformed_labyrinth(Labyrinth* labyrinth);

/**
 * @brief Creates a labyrinth path by selectively breaking walls between cells.
 * 
 * Randomly breaks walls between cells to form a solvable path throughout the labyrinth.
 * Adds an entry and exit to make the labyrinth playable.
 * 
 * @param labyrinth Pointer to the labyrinth structure to modify.
 * 
 * @return void
 * 
 * @note This version is less efficient than create_recursive_labyrinth_path()
 */
void create_labyrinth_path(Labyrinth* labyrinth);

/**
 * @brief Recursively generates paths in the labyrinth, based on a given difficulty level.
 * 
 * Creates a path recursively and optionally adds difficulty elements such as monsters and imperfect labyrinth.
 * 
 * @param labyrinth Pointer to the labyrinth structure to modify.
 * @param difficult Flag indicating whether to add monsters and imperfect labyrinth (1 for true).
 * 
 * @return void
 */
void init_create_recursive_labyrinth_path(Labyrinth* labyrinth, int difficult);

/**
 * @brief Recursively creates a labyrinth path by exploring neighboring cells.
 * 
 * Traverses and connects cells recursively to form paths in the labyrinth.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * @param current_row Row index of the current cell.
 * @param current_column Column index of the current cell.
 * 
 * @return void
 * 
 * @note This version is more efficient than create_labyrinth_path()
 */
void create_recursive_labyrinth_path(Labyrinth* labyrinth, int current_row, int current_column);

/**
 * @brief Initializes a cell structure within the labyrinth.
 * 
 * Allocates memory for a cell structure with given row and column coordinates.
 * 
 * @param lab The labyrinth containing the cell.
 * @param row The row index of the cell.
 * @param column The column index of the cell.
 * 
 * @return Pointer to the initialized cell, or NULL if coordinates are out of bounds.
 */
Lab_cell* init_lab_cell(Labyrinth lab, int row, int column);

/**
 * @brief Retrieves all possible neighboring cells for a given cell in the labyrinth.
 * 
 * Initializes neighboring cells and shuffles them to provide a randomized list of accessible neighbors.
 * 
 * @param labyrinth The labyrinth containing the cell.
 * @param current_row Row index of the current cell.
 * @param current_column Column index of the current cell.
 * @param neighbours Array to store neighboring cells.
 * 
 * @return The number of valid neighboring cells found.
 */
int get_possible_neighbours(Labyrinth labyrinth, int current_row, int current_column, Lab_cell* neighbours);

/**
 * @brief Shuffles an array of neighboring cells using the Fisher-Yates algorithm.
 * 
 * Randomizes the order of neighboring cells in the array to aid in labyrinth path creation.
 * 
 * @param neighbours Array of neighboring cells to shuffle.
 * @param size The number of cells in the array.
 * 
 * @return void
 */
void shuffle_neighbours(Lab_cell* neighbours, int size);

/**
 * @brief Selects a random cell in the labyrinth.
 * 
 * Chooses a random path cell within the labyrinth dimensions.
 * 
 * @param lab The labyrinth containing the cell.
 * @param random_row Pointer to store the row index of the selected cell.
 * @param random_column Pointer to store the column index of the selected cell.
 * 
 * @return void
 */
void pull_random_cell(Labyrinth lab, int* random_row, int* random_column);

/**
 * @brief Selects a random cell that does not contain a wall, entry, or exit within the labyrinth.
 * 
 * Chooses a random cell that does not contain a wall, entry, or exit.
 * 
 * @param lab The labyrinth to select the cell from.
 * @param random_row Pointer to store the selected cell's row index.
 * @param random_column Pointer to store the selected cell's column index.
 * 
 * @return void
 */
void pull_random_empty_cell(Labyrinth lab, int* random_row, int* random_column);

/**
 * @brief Selects a random breakable wall within the labyrinth.
 * 
 * Chooses a random wall location that can be broken to create a path.
 * 
 * @param lab The labyrinth containing the walls.
 * @param random_row Pointer to store the selected wall's row index.
 * @param random_column Pointer to store the selected wall's column index.
 * 
 * @return void
 */
void pull_breakable_wall(Labyrinth lab, int* random_row, int* random_column);

/**
 * @brief Unifies two rooms in the labyrinth by assigning them the same cell value.
 * 
 * Replaces all occurrences of a room identifier with a target room identifier to merge rooms.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * @param number_to_place The identifier of the target room.
 * @param number_to_replace The identifier of the room to be unified.
 * 
 * @return void
 */
void unify_room_number(Labyrinth* labyrinth, int number_to_place, int number_to_replace);

/**
 * @brief Adds entry and exit to the labyrinth for gameplay purposes.
 * 
 * Sets specific cells as the entry and exit within the labyrinth.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * 
 * @return 1 on success.
 */
int make_labyrinth_playable(Labyrinth* labyrinth);

/**
 * @brief Makes the labyrinth imperfect by randomly breaking additional walls.
 * 
 * Breaks a specified number of walls to create loops, making the labyrinth less linear.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * 
 * @return void
 */
void make_lab_unperfect(Labyrinth* labyrinth);

/**
 * @brief Adds score-related objects to the labyrinth.
 * 
 * Places bonus cells, trap cells, and a key (and lock the exit) to enhance gameplay mechanics.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * @param nb_bonus Number of bonus cells to add.
 * @param nb_trap Number of trap cells to add.
 * 
 * @return void
 */
void add_score_mecanics(Labyrinth* labyrinth, int nb_bonus, int nb_trap);

/**
 * @brief Adds a key and locks the exit of the labyrinth.
 * 
 * Places the key randomly in the labyrinth and locks the exit.
 * 
 * @param labyrinth Pointer to the labyrinth structure.
 * 
 * @return void
 */
void add_key_and_lock_door(Labyrinth* labyrinth);

/**
 * @brief Adds a specified number of objects (traps, bonuses, etc) to the labyrinth.
 * 
 * Randomly places objects of a specified type in the labyrinth.
 * 
 * @param lab Pointer to the labyrinth structure.
 * @param nb_objet Number of objects to place.
 * @param object_to_place The type of object to place (TRAP_CELL, BONUS_CELL, etc).
 * 
 * @return void
 */
void add_objects(Labyrinth* labyrinth, int nb_objet, CellType object_to_place);

/**
 * @brief Creates a deep copy of the labyrinth structure, including monsters and layout.
 * 
 * Duplicates the labyrinth's layout, cells, and monster positions to create an independent copy.
 * 
 * @param labyrinth The labyrinth to copy.
 * 
 * @return Pointer to the copied labyrinth structure.
 */
Labyrinth* copy_labyrinth(Labyrinth labyrinth);

/**
 * @brief Frees memory allocated to a labyrinth structure and its associated elements.
 * 
 * Deallocates memory for cells, monsters, and the labyrinth structure itself.
 * 
 * @param labyrinth Pointer to the labyrinth to destroy.
 * 
 * @return void
 */
void destroy_labyrinth(Labyrinth* labyrinth);

#endif