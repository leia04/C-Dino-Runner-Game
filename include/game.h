#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include "constants.h"

int check_collision(Position dino, Position obstacle, int crouching);
int check_item_collision(Position dino, Position item);

void apply_item_effect(int item_type, int *delay, int *reverse_controls, int *theme);

void reset_game(
    Position *dino,
    Position obstacles[],
    Position clouds[],
    int *score,
    int *game_over,
    int *initial_run,
    int *jumping,
    int *jump_counter,
    int *delay,
    int *max_obstacles,
    int *last_speed_increase,
    int *last_obstacle_increase,
    int *crouching,
    int *crouch_counter,
    Position *item,
    int *item_active,
    int *reverse_controls,
    int *theme
);

void generate_obstacle(Position *obstacle, int min_x);
