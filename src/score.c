#include "score.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void save_score(Player player) {
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL) {
        char time_str[26];
        struct tm *tm_info = localtime(&player.time);
        strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        fprintf(file, "Player: %s, Character: %s, Score: %d, Time: %s\n",
                player.name, player.character_name, player.score, time_str);
        fclose(file);
    }
}

int check_name_exists(const char* name) {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char existing_name[50];
        if (sscanf(line, "Player: %49[^,],", existing_name) == 1) {
            if (strcmp(existing_name, name) == 0) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

int read_high_score(void) {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) return 0;

    int high_score = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int score;
        if (sscanf(line, "Player: %*[^,], Character: %*[^,], Score: %d,", &score) == 1) {
            if (score > high_score) high_score = score;
        }
    }
    fclose(file);
    return high_score;
}

int read_all_scores(int *all_scores) {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) return 0;

    int total = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int score;
        if (sscanf(line, "Player: %*[^,], Character: %*[^,], Score: %d,", &score) == 1) {
            all_scores[total++] = score;
        }
    }
    fclose(file);
    return total;
}

int get_rank(int score, int *all_scores, int total_scores) {
    int rank = 1;
    for (int i = 0; i < total_scores; i++) {
        if (score < all_scores[i]) rank++;
    }
    return rank;
}

int read_scores(ScoreEntry *scores) {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) return 0;

    int total = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Player: %[^,], Character: %[^,], Score: %d, Time: %[^\n]",
                   scores[total].name,
                   scores[total].character_name,
                   &scores[total].score,
                   scores[total].time_str) == 4) {
            total++;
        }
    }
    fclose(file);
    return total;
}
