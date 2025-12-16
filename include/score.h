#pragma once
#include "constants.h"

void save_score(Player player);
int check_name_exists(const char* name);

int read_high_score(void);
int read_all_scores(int *all_scores);
int get_rank(int score, int *all_scores, int total_scores);

int read_scores(ScoreEntry *scores);
