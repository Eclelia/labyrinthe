/**
 * @file monster.h
 * @brief Functions for creating, moving, and managing monsters in the labyrinth.
 */

#ifndef MONSTER_H
#define MONSTER_H

#include "game_struct.h"

/** 
 * @def RATIO_GHOST
 * @brief Determines the ratio for ghost generation in the labyrinth.
 */
#define RATIO_GHOST 65
/**  
 * @def RATIO_TROLL(nb_bonuses)
 * @brief Calculates the number of trolls based on the number of bonus cells.
 */
#define RATIO_TROLL(nb_bonuses) (nb_bonuses/3) 
/**  
 * @def MAX_DISTANCE_FROM_SPAWN
 * @brief restricts troll movement : they can't go too far from their spawn.
 */
#define MAX_DISTANCE_FROM_SPAWN 6

/**
 * @enum Penality
 * @brief Enumerates the penalties associated with different monster types.
 */
typedef enum{
    GHOST_P = -10,
    TROLL_P = -10,
} Penality;

/**
 * @struct Monster
 * @brief Represents a monster in the labyrinth.
 * 
 * The structure defines the position, type, and penalty associated with a monster in the labyrinth.
 * 
 * @var Monster::column
 * The initial column position of the monster in the labyrinth.
 * 
 * @var Monster::row
 * The initial row position of the monster in the labyrinth.
 * 
 * @var Monster::current_column
 * The current column position of the monster in the labyrinth.
 * 
 * @var Monster::current_row
 * The current row position of the monster in the labyrinth.
 * 
 * @var Monster::type
 * The type of the monster, defined as a CellType (e.g., GHOST or TROLL).
 * 
 * @var Monster::penalty
 * The penalty associated with the monster, defined as a Penality (e.g., GHOST_P or TROLL_P).
 */
struct Monster{
    int column;
    int row;
    int current_column;
    int current_row;
    CellType type;
    Penality penalty;
};

/**
 * @brief Creates a new monster.
 * 
 * This function creates a new monster with the given row, column, type, and penalty.
 * The monster is initialized with its position and attributes.
 * 
 * @param row The row position of the monster.
 * @param column The column position of the monster.
 * @param type The type of the monster (ghost, troll, etc).
 * @param penalty The penalty associated with the monster.
 * @return A pointer to the newly created monster.
 */
Monster* create_monster(int row, int column, CellType type, Penality penalty);

/**
 * @brief Creates a ghost monster.
 * 
 * This function creates a ghost monster at the specified row and column. 
 * The ghost is created using the `create_monster` function with predefined ghost type and penalty.
 * 
 * @param row The row position of the ghost.
 * @param column The column position of the ghost.
 * @return A pointer to the newly created ghost monster.
 */
Monster* create_ghost(int row, int column);

/**
 * @brief Creates a troll monster.
 * 
 * This function creates a troll monster at the specified row and column. 
 * The troll is created using the `create_monster` function with predefined troll type and penalty.
 * 
 * @param row The row position of the troll.
 * @param column The column position of the troll.
 * @return A pointer to the newly created troll monster.
 */
Monster* create_troll(int row, int column);

/**
 * @brief Adds monsters to the labyrinth.
 * 
 * This function calculates the number of ghosts and trolls to add based on the size of the labyrinth
 * and the number of bonus cells. It then allocates memory for the monsters and adds the ghosts and
 * trolls to the labyrinth.
 * 
 * @param lab A pointer to the labyrinth where the monsters are to be added.
 */
void add_monsters(Labyrinth* lab);

/**
 * @brief Adds a ghost monster to the labyrinth.
 * 
 * This function randomly selects a cell in the labyrinth and places a ghost monster
 * in that cell, ensuring it is not an entry or exit cell.
 * 
 * @param lab A pointer to the labyrinth where the ghost is to be placed.
 * 
 * @note A ghost can be placed where another one is already. This is intentional.
 */
void add_ghost(Labyrinth* lab);

/**
 * @brief Adds a troll monster to the labyrinth.
 * 
 * This function randomly selects a bonus cell and places a troll monster on that cell.
 * 
 * @param lab A pointer to the labyrinth where the troll is to be placed.
 * @param nb_bonuses The total number of bonus cells in the labyrinth.
 * 
 * @note A troll can be placed where another one is already. This is intentional.
 */
void add_troll(Labyrinth* lab, int nb_bonuses);

/**
 * @brief Chooses a random direction for monster movement.
 * 
 * This function randomly selects a direction (row and column) for monster movement.
 * The direction is constrained to avoid diagonal movements.
 * 
 * @param d_row A pointer to the chosen row direction.
 * @param d_column A pointer to the chosen column direction.
 */
void choose_direction(int* d_row, int* d_column);

/**
 * @brief Moves all monsters in the labyrinth.
 * 
 * This function iterates through all monsters in the labyrinth and moves each one according
 * to its type (ghosts follow a different movement logic than trolls).
 * 
 * @param lab A pointer to the labyrinth where the monsters are located.
 * 
 * @note by default, a monster will have the same movements as a troll.
 */
void move_monsters(Labyrinth* lab);

/**
 * @brief Moves a ghost monster in the labyrinth.
 * 
 * This function attempts to move a ghost in a random direction within the labyrinth.
 * The ghost can only move to valid, non-restricted cells (not an entry, exit, or closed exit).
 * 
 * @param lab A pointer to the labyrinth where the ghost is located.
 * @param monster A pointer to the ghost monster to move.
 * @return The type of monster (GHOST).
 */
int move_ghost(Labyrinth* lab, Monster* monster);

/**
 * @brief Moves a troll monster in the labyrinth.
 * 
 * This function attempts to move a troll in a random direction within the labyrinth.
 * The troll can only move to valid, non-restricted cells (not a wall, entry, exit, or closed exit).
 * The troll's movement may also be constrained by its proximity to bonus cells.
 * 
 * @param lab A pointer to the labyrinth where the troll is located.
 * @param monster A pointer to the troll monster to move.
 * @return The type of monster (TROLL).
 */
int move_troll(Labyrinth* lab, Monster* monster);

/**
 * @brief Calculates the Manhattan distance from the monster's spawn location to a given cell in the labyrinth.
 * 
 * The spawn location is defined by the `row` and `column` attributes of the Monster struct.
 * This function calculates the absolute difference in rows and columns between the 
 * spawn point and the target location `(next_row, next_column)`.
 * 
 * @param monster A Monster whose spawn location is used for the calculation.
 * @param next_row The row index of the target cell.
 * @param next_column The column index of the target cell.
 * @return int The Manhattan distance between the spawn location and the target cell.
 */
int distance_from_spawn(Monster monster, int next_row, int next_column);

/**
 * @brief Destroys a monster and frees allocated memory.
 * 
 * This function deallocates the memory used by a monster.
 * 
 * @param monster A pointer to the monster to destroy.
 */
void destroy_monster(Monster* monster);

#endif