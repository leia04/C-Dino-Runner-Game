#pragma once
#include <ncurses.h>
#include "constants.h"

void get_player_name(Player *player);
Character select_character(char *selected_character_name);

void print_game_over(Player player, int *scores, int try_count);
