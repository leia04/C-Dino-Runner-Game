#pragma once
#include <time.h>

#define INITIAL_DELAY 50000
#define DINO_HEIGHT 3
#define DINO_WIDTH 5
#define OBSTACLE_WIDTH 2
#define GROUND_Y 30
#define JUMP_HEIGHT 3
#define JUMP_DELAY 8
#define INITIAL_OBSTACLES 2
#define MAX_OBSTACLES 6
#define MIN_OBSTACLE_DISTANCE 40
#define SPEED_INCREASE_INTERVAL 300
#define SPEED_INCREASE_AMOUNT 1500
#define OBSTACLE_INCREASE_INTERVAL 1000
#define MIN_DELAY 20000
#define CROUCH_DURATION 10
#define MAX_CLOUDS 5

#define OBSTACLE_MIN_HEIGHT (GROUND_Y + 1)
#define OBSTACLE_MAX_HEIGHT (GROUND_Y - 3)

#define ITEM_SPEED_CHANGE 1
#define ITEM_REVERSE_CONTROLS 2
#define ITEM_TOGGLE_THEME 3

typedef struct { int x, y; } Position;

typedef struct {
    char name[50];
    int score;
    int is_restart;
    time_t time;
    char character_name[50];
} Player;

typedef struct {
    char* name;
    char* idle[DINO_HEIGHT];
    char* crouch[DINO_HEIGHT];
} Character;

typedef struct {
    char name[50];
    char character_name[50];
    int score;
    char time_str[26];
} ScoreEntry;
