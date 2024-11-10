#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include "labyrinth.h"
#define NAME_SIZE 255 //UNIX max authorized size for filename

void ask_lab_size(int* row, int* column);

void ask_difficulty(int* difficulty);

void ask_lab_name(int size, char name[size]);

void save_into_file(Labyrinth lab, const char* filename);

Labyrinth* load_lab(char* name_out);

Labyrinth* load_from_file(const char* filename);

#endif