#include "ui.h"
#include "characters.h"
#include "score.h"
#include <string.h>
#include <stdio.h>

void get_player_name(Player *player) {
    echo();
    clear();
    mvprintw(LINES / 2 - 2, COLS / 2 - 10, "Enter your name: ");
    getnstr(player->name, 49);
    noecho();

    if (strlen(player->name) == 0) {
        static int unknown_counter = 1;
        char temp_name[50];
        do {
            snprintf(temp_name, 50, "unknown_%d", unknown_counter++);
        } while (check_name_exists(temp_name));
        strncpy(player->name, temp_name, 50);
    }

    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 20, "Game Instructions:");
    mvprintw(LINES / 2 - 8,  COLS / 2 - 20, "1. Use 'Space' or 'Up arrow' to jump.");
    mvprintw(LINES / 2 - 6,  COLS / 2 - 20, "2. Use 'Down arrow' to crouch.");
    mvprintw(LINES / 2 - 4,  COLS / 2 - 20, "3. Avoid obstacles and collect items.");
    mvprintw(LINES / 2 - 2,  COLS / 2 - 20, "4. Press 'p' to pause/resume the game.");

    mvprintw(LINES / 2,      COLS / 2 - 20, "Item Descriptions:");
    mvprintw(LINES / 2 + 2,  COLS / 2 - 20, "[]: Changes speed.");
    mvprintw(LINES / 2 + 4,  COLS / 2 - 20, "><: Reverses controls.");
    mvprintw(LINES / 2 + 6,  COLS / 2 - 20, "**: Switch day/night.");

    mvprintw(LINES / 2 + 8,  COLS / 2 - 20, "Press any key to continue.");
    getch();
}

Character select_character(char *selected_character_name) {
    int ch;
    int selected = 0;

    while (1) {
        clear();
        mvprintw(5, 5, "Select your character (Left/Right + Enter):");

        for (int i = 0; i < 5; i++) {
            if (i == selected) attron(A_REVERSE);
            mvprintw(7,  5 + i * 15, "%s", characters[i].name);
            mvprintw(8,  5 + i * 15, "%s", characters[i].idle[0]);
            mvprintw(9,  5 + i * 15, "%s", characters[i].idle[1]);
            mvprintw(10, 5 + i * 15, "%s", characters[i].idle[2]);
            attroff(A_REVERSE);
        }

        ch = getch();
        if (ch == KEY_RIGHT) selected = (selected + 1) % 5;
        else if (ch == KEY_LEFT) selected = (selected + 4) % 5;
        else if (ch == '\n') {
            strcpy(selected_character_name, characters[selected].name);
            break;
        }
        refresh();
    }
    return characters[selected];
}

void print_game_over(Player player, int *scores, int try_count) {
    int all_scores[1000];
    int total_scores = read_all_scores(all_scores);

    clear();
    mvprintw(5, 0, "Game Over!");
    mvprintw(7, 0, "Final Scores:");
    for (int i = 0; i < try_count; i++) mvprintw(8 + i, 0, "%d try: %d", i + 1, scores[i]);

    mvprintw(9 + try_count, 0, "Ranks:");
    for (int i = 0; i < try_count; i++) {
        int current_total = total_scores + i + 1;
        all_scores[current_total - 1] = scores[i];
        int rank = get_rank(scores[i], all_scores, current_total);
        mvprintw(10 + try_count + i, 0, "%d try: Rank %d out of %d", i + 1, rank, current_total);
    }

    ScoreEntry entries[1000];
    int count = read_scores(entries);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (entries[j].score < entries[j + 1].score) {
                ScoreEntry tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
        }
    }

    mvprintw(15, 0, "Top 10 Scores:");
    mvprintw(16, 0, "+------+-----------------+------------+-------+---------------------+");
    mvprintw(17, 0, "| Rank | Player          | Character  | Score | Time                |");
    mvprintw(18, 0, "+------+-----------------+------------+-------+---------------------+");
    for (int i = 0; i < count && i < 10; i++) {
        mvprintw(19 + i, 0, "| %-4d | %-15s | %-10s | %-5d | %-19s |",
                 i + 1, entries[i].name, entries[i].character_name, entries[i].score, entries[i].time_str);
    }
    mvprintw(19 + (count < 10 ? count : 10), 0, "+------+-----------------+------------+-------+---------------------+");
    refresh();
    getch();
}
