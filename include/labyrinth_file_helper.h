/**
 * @file labyrinth_file_helper.h
 * @brief Contains functions for saving and loading labyrinth configurations to and from files.
 */

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include "labyrinth.h"
/** 
 * @def NAME_SIZE
 * @brief Defines the max lenght a name (by default : UNIX max authorized size for filename).
 */
#define NAME_SIZE 255

/**
 * @brief Asks the user to input the size (height and width) of the labyrinth.
 * 
 * This function asks the user to input the height and width of the labyrinth.
 * The values must be odd numbers, otherwise they are invalid.
 * 
 * @param row A pointer to an integer where the height of the labyrinth is stored.
 * @param column A pointer to an integer where the width of the labyrinth is stored.
 */
void ask_lab_size(int* row, int* column);

/**
 * @brief Prompts the user for the labyrinth difficulty level.
 * 
 * This function prompts the user to select either "easy" or "hard" mode, ensuring that 
 * only valid options are accepted (0 for easy, 1 for hard).
 * 
 * @param difficulty A pointer to store the selected difficulty level.
 */
void ask_difficulty(int* difficulty);

/**
 * @brief Prompts the user for a labyrinth name.
 * 
 * This function requests the user to input a name for the labyrinth, ensuring that the name
 * length is within acceptable bounds.
 * 
 * @param size The maximum allowable size for the labyrinth name.
 * @param name A buffer to store the entered labyrinth name.
 */
void ask_lab_name(int size, char name[size]);

/**
 * @brief Saves a labyrinth configuration into a readable file.
 * 
 * This function saves the labyrinth's dimensions, layout, and monster information 
 * into a file with the given filename and a ".cfg" extension in the directory specified by DATA_PATH.
 * 
 * @param lab The labyrinth to save.
 * @param filename The name of the file where the labyrinth will be saved (without the extension).
 */
void save_into_file(Labyrinth lab, const char* filename);

/**
 * @brief Loads a labyrinth from a file.
 * 
 * This function loads a labyrinth from a file with the given filename. It reads 
 * the labyrinth's dimensions, layout, and monster data. If the file is not found 
 * or if the labyrinth configuration is corrupted, it returns NULL.
 * 
 * @param name_out The name of the loaded labyrinth file.
 * @return A pointer to the loaded labyrinth.
 */
Labyrinth* load_lab(char* name_out);

/**
 * @brief Loads a labyrinth from a file with a specific filename.
 * 
 * This function reads a labyrinth configuration from a file and loads it into 
 * memory. If the labyrinth file is corrupted or cannot be read, it returns NULL.
 * 
 * @param filename The name of the file containing the labyrinth data (without the extension).
 * @return A pointer to a Labyrinth structure containing the loaded data.
 */
Labyrinth* load_from_file(const char* filename);

#endif