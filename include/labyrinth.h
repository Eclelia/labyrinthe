/**
 * @file labyrinth.h
 * @brief Functions to interact with and manipulate the labyrinth grid.
 */

#ifndef LABYRINTH_H
#define LABYRINTH_H
#define LARGEUR 11
#define LONGUEUR 25
#define STARTING_ROW 0
#define STARTING_COLUMN 1

#include "game_struct.h"
#include "monster.h"

struct Labyrinth{
    int* game;
    int largeur; //TODO refacto les largeur en column
    int longueur; //TODO refacto les longueur en row
    int n_monsters;
    Monster* monsters;
};

struct Labyrinth_cell{
    int row;
    int column;
};

/**
 * @brief Retrieves the value of a specific cell in the labyrinth.
 * 
 * This function retrieves the value at the given coordinates (i, j) in the labyrinth.
 * If the coordinates are outside the bounds of the labyrinth, it returns UNDEFINED.
 * 
 * @param lab The labyrinth structure.
 * @param i The row index of the cell.
 * @param j The column index of the cell.
 * @return The value stored in the cell at coordinates (i, j), or UNDEFINED if out of bounds.
 */
int get_cell(Labyrinth lab, int i, int j);

/**
 * @brief Counts the number of bonus cells in the labyrinth.
 * 
 * This function iterates over the labyrinth grid and counts the number of cells
 * that contain a bonus. A bonus is represented by the constant BONUS_CELL.
 * 
 * @param lab The labyrinth structure.
 * @return The number of bonus cells in the labyrinth.
 */
int get_nb_bonus(Labyrinth lab);

/**
 * @brief Retrieves the position of the nth bonus cell in the labyrinth.
 * 
 * This function searches for the nth occurrence of a bonus cell in the labyrinth.
 * If the nth bonus is found, the row and column indices of the cell are returned
 * via the row and column pointers. If the nth bonus is not found, the function returns 0.
 * 
 * @param lab The labyrinth structure.
 * @param nth The index of the bonus to find (1-based).
 * @param row A pointer to store the row index of the nth bonus.
 * @param column A pointer to store the column index of the nth bonus.
 * @return 1 if the nth bonus was found, 0 if it was not found.
 */
int get_nth_bonus(Labyrinth lab, int nth, int* row, int* column);

/**
 * @brief Sets the value of a specific cell in the labyrinth.
 * 
 * This function sets the value of the cell at coordinates (i, j) to the specified value.
 * If the coordinates are outside the bounds of the labyrinth, it returns -1 to indicate an error.
 * 
 * @param lab A pointer to the labyrinth structure to modify.
 * @param i The row index of the cell.
 * @param j The column index of the cell.
 * @param value The value to set at the cell.
 * @return 0 if the cell was successfully set, -1 if the coordinates are out of bounds.
 */
int set_cell(Labyrinth* lab, int i, int j, int value);

/**
 * @brief Clears the input buffer.
 * 
 * This function consumes all characters in the input buffer until a newline character
 * is encountered. It is typically used to clear any extra characters left in the buffer
 * after reading input from the user.
 */
void empty_buffer();

#endif