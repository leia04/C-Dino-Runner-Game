#include "game.h"

int check_collision(Position dino, Position obstacle, int crouching) {
    int dino_bottom = dino.y + DINO_HEIGHT;
    int dino_top = dino.y;
    if (crouching) {
        dino_bottom = dino.y + DINO_HEIGHT - 1;
        dino_top = dino.y + 1;
    }
    return (dino_bottom > obstacle.y) &&
           (dino_top <= obstacle.y) &&
           (dino.x < obstacle.x + OBSTACLE_WIDTH) &&
           (dino.x + DINO_WIDTH > obstacle.x);
}

int check_item_collision(Position dino, Position item) {
    return (dino.y <= item.y + 1) &&
           (dino.y + DINO_HEIGHT >= item.y) &&
           (dino.x < item.x + 2) &&
           (dino.x + DINO_WIDTH > item.x);
}

void apply_item_effect(int item_type, int *delay, int *reverse_controls, int *theme) {
    switch (item_type) {
        case ITEM_SPEED_CHANGE:
            *delay += (rand() % 2 ? -10000 : 10000);
            if (*delay < MIN_DELAY) *delay = MIN_DELAY;
            if (*delay > 100000) *delay = 100000;
            break;
        case ITEM_REVERSE_CONTROLS:
            *reverse_controls = !(*reverse_controls);
            break;
        case ITEM_TOGGLE_THEME:
            *theme = !(*theme);
            if (*theme) bkgd(COLOR_PAIR(2));
            else        bkgd(COLOR_PAIR(1));
            break;
    }
}

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
) {
    dino->x = 5;
    dino->y = GROUND_Y;

    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i].x = COLS + i * (MIN_OBSTACLE_DISTANCE + (rand() % MIN_OBSTACLE_DISTANCE));
        obstacles[i].y = GROUND_Y - (rand() % (GROUND_Y - OBSTACLE_MAX_HEIGHT + 1));
        if (obstacles[i].y < OBSTACLE_MAX_HEIGHT) obstacles[i].y = OBSTACLE_MAX_HEIGHT;
        if (obstacles[i].y > OBSTACLE_MIN_HEIGHT) obstacles[i].y = OBSTACLE_MIN_HEIGHT;
    }

    for (int i = 0; i < MAX_CLOUDS; i++) {
        clouds[i].x = rand() % COLS;
        clouds[i].y = rand() % (GROUND_Y / 2);
    }

    *score = 0;
    *game_over = 0;
    *initial_run = 1;
    *jumping = 0;
    *jump_counter = 0;

    *delay = INITIAL_DELAY;
    *max_obstacles = INITIAL_OBSTACLES;
    *last_speed_increase = 0;
    *last_obstacle_increase = 0;

    *crouching = 0;
    *crouch_counter = 0;

    *item_active = 0;
    *reverse_controls = 0;
    *theme = 0;
    bkgd(COLOR_PAIR(1));

    item->x = -1;
    item->y = -1;
}

void generate_obstacle(Position *obstacle, int min_x) {
    obstacle->x = min_x + MIN_OBSTACLE_DISTANCE + (rand() % MIN_OBSTACLE_DISTANCE);
    obstacle->y = GROUND_Y - (rand() % (GROUND_Y - OBSTACLE_MAX_HEIGHT + 1));
    if (obstacle->y < OBSTACLE_MAX_HEIGHT) obstacle->y = OBSTACLE_MAX_HEIGHT;
    if (obstacle->y > OBSTACLE_MIN_HEIGHT) obstacle->y = OBSTACLE_MIN_HEIGHT;
}
