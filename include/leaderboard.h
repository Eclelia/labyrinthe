#ifndef LEADERBOARD_H
#define LEADERBOARD_H

typedef struct Player_score{
    char* name;
    int score;
} P_score;

typedef struct Leaderboard{
    Player_score* score_list;
    unsigned int nb_of_scores;
} Leaderboard;

Leaderboard* init_leaderboard();

void save_leaderboard(Leaderboard lb);

Leaderboard* load_leaderboard(const char* filename);

#endif