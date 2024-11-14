/**
 * @file leaderboard.h
 * @brief Functions for managing the leaderboard and player scores.
 */

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define LEADERBOARD_SIZE 10
#include "game_struct.h"

struct Player_score{
    char* name;
    int score;
};

struct Leaderboard{
    P_score* score_list;
    int nb_of_scores;
};

/**
 * @brief Initializes a new leaderboard.
 * 
 * This function allocates memory for a new leaderboard and initializes the number of scores
 * to zero. It also allocates memory for the score list with an initial size of LEADERBOARD_SIZE entries.
 * 
 * @return A pointer to the initialized leaderboard.
 */
Leaderboard* init_leaderboard();

/**
 * @brief Initializes a new player score.
 * 
 * This function allocates memory for a new player score, copies the player’s name, and assigns
 * the provided score. The name is dynamically allocated based on its length.
 * 
 * @param name The name of the player.
 * @param score The score of the player.
 * @return A pointer to the newly initialized player score.
 */
P_score* init_player_score(const char* name, int score);

/**
 * @brief Destroys a leaderboard and frees all allocated memory.
 * 
 * This function deallocates all memory used by the leaderboard, including the memory
 * for the player scores and the score list.
 * 
 * @param lb A pointer to the leaderboard to destroy.
 */
void destroy_leaderboard(Leaderboard* lb);

/**
 * @brief Destroys a player score and frees the allocated memory.
 * 
 * This function deallocates all memory used by a player score, including the memory
 * for the player's name.
 * 
 * @param pc A pointer to the player score to destroy.
 */
void destroy_player_score(P_score* pc);

/**
 * @brief Saves the leaderboard to a file.
 * 
 * This function writes the leaderboard’s scores and player names to a file. The file
 * is named using the provided filename and the ".score" extension.
 * 
 * @param lb The leaderboard to save.
 * @param filename The name of the file to save the leaderboard to (without the extension).
 */
void save_leaderboard(Leaderboard lb, const char* filename);

/**
 * @brief Loads a leaderboard from a file.
 * 
 * This function prompts the user for a filename and loads the leaderboard data
 * from the specified file.
 * 
 * @return A pointer to the loaded leaderboard, or NULL if the loading failed.
 */
Leaderboard* load_leaderboard();


/**
 * @brief Loads a leaderboard from a specific file.
 * 
 * This function loads the leaderboard data from a file with the specified filename.
 * It reads the number of scores, player names, and scores into a newly allocated
 * leaderboard structure.
 * 
 * @param filename The name of the file to load the leaderboard from (without the extension). 
 * @return A pointer to the loaded leaderboard, or NULL if the file could not be opened.
 */
Leaderboard* load_lb_from_file(const char* filename);

/**
 * @brief Retrieves the lowest score in the leaderboard.
 * 
 * This function returns the score of the player with the lowest score, which is
 * the last score in the sorted leaderboard.
 * 
 * @param lb The leaderboard structure.
 * @return The lowest score in the leaderboard.
 */
int get_lowest_score(Leaderboard lb);

/**
 * @brief Prompts the user for their name.
 * 
 * This function asks the user to enter their name, ensuring that the name is
 * not empty and does not exceed the specified size limit.
 * 
 * @param size The maximum size of the player’s name.
 * @param name A buffer to store the player’s name.
 */
void ask_player_name(int size, char name[size]);

/**
 * @brief Adds a player to the leaderboard.
 * 
 * This function adds a player to the leaderboard, ensuring the leaderboard does not
 * exceed the LEADERBOARD_SIZE constant. If there is space, the new score is added; otherwise, the
 * lowest score is replaced. The leaderboard is then sorted and saved to the file.
 * 
 * @param lb A pointer to the leaderboard structure.
 * @param filename The name of the file to save the updated leaderboard (without the extension).
 * @param name The name of the player.
 * @param score The score of the player.
 */
void add_player(Leaderboard* lb, const char* filename, const char* name, int score);

/**
 * @brief Sorts the leaderboard in descending order of scores.
 * 
 * This function sorts the leaderboard’s scores using the `qsort` function and the
 * `compare_scores` comparison function.
 * 
 * @param lb A pointer to the leaderboard to sort.
 */
void sort_player(Leaderboard* lb);

/**
 * @brief Comparison function for sorting player scores.
 * 
 * This function compares two player scores for sorting purposes. It is used by the
 * `qsort` function to sort players in descending order based on their scores.
 * 
 * @param obj_a A pointer to the first player score to compare.
 * @param obj_b A pointer to the second player score to compare.
 * @return A negative integer if obj_a's score is less than obj_b's score,
 *         a positive integer if obj_a's score is greater, or 0 if they are equal.
 */
int compare_scores(const void *player_a, const void *player_b);

#endif