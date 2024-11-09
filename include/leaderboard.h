#ifndef LEADERBOARD_H
#define LEADERBOARD_H

typedef struct Player_score{
    char* name;
    int score;
} P_score;

typedef struct Leaderboard{
    P_score* score_list;
    int nb_of_scores;
} Leaderboard;

Leaderboard* init_leaderboard();

P_score* init_player_score(const char* name, int score);

void destroy_player_score(P_score* pc);

void save_leaderboard(Leaderboard lb, const char* filename);

Leaderboard* load_leaderboard();

Leaderboard* load_lb_from_file(const char* filename);

void destroy_leaderboard(Leaderboard* lb);

void display_lb(Leaderboard lb);

#endif