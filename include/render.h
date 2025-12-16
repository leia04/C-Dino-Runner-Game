#pragma once
#include <ncurses.h>
#include "constants.h"

void init_colors(void);

void draw_dino(Position dino, int crouching, Character character);
void draw_obstacle(Position obstacle);
void draw_cloud(Position cloud);
void draw_star(Position star);

void draw_sun(void);
void draw_moon(void);

void draw_item(Position item, int item_type);
