#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

typedef struct Monster Monster;
typedef struct Labyrinth Labyrinth;
typedef struct Labyrinth_cell Lab_cell;
typedef struct Leaderboard Leaderboard;
typedef struct Player_score P_score;

typedef enum{
    PATH = 1,
    WALL = 0,
    UNDEFINED = -10,
    PLAYER = -1,
    EXIT = -2,
    CLOSED_EXIT = -3,
    KEY = -4,
    BONUS_CELL = -5,
    TRAP_CELL = -6,
    GHOST = -7,
    TROLL = -8
} CellType;

#endif