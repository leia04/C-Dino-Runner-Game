#include "render.h"

void init_colors(void) {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

void draw_dino(Position dino, int crouching, Character character) {
    if (crouching) {
        mvprintw(dino.y + 1, dino.x, "%s", character.crouch[0]);
        mvprintw(dino.y + 2, dino.x, "%s", character.crouch[1]);
    } else {
        mvprintw(dino.y, dino.x, "%s", character.idle[0]);
        mvprintw(dino.y + 1, dino.x, "%s", character.idle[1]);
        mvprintw(dino.y + 2, dino.x, "%s", character.idle[2]);
    }
}

void draw_obstacle(Position obstacle) { mvprintw(obstacle.y, obstacle.x, "##"); }
void draw_cloud(Position cloud)       { mvprintw(cloud.y, cloud.x, "~~~"); }
void draw_star(Position star)         { mvprintw(star.y, star.x, "*"); }

void draw_sun(void) {
    mvprintw(2, COLS - 10, " \\ /");
    mvprintw(3, COLS - 10, "- O -");
    mvprintw(4, COLS - 10, " / \\");
}

void draw_moon(void) {
    mvprintw(2, COLS - 10, "   _  ");
    mvprintw(3, COLS - 10, "  / \\ ");
    mvprintw(4, COLS - 10, " |  | ");
    mvprintw(5, COLS - 10, "  \\_\\ ");
}

void draw_item(Position item, int item_type) {
    switch (item_type) {
        case ITEM_SPEED_CHANGE:
            mvprintw(item.y, item.x, "[]");
            mvprintw(item.y + 1, item.x, "[]");
            break;
        case ITEM_REVERSE_CONTROLS:
            mvprintw(item.y, item.x, "><");
            mvprintw(item.y + 1, item.x, "><");
            break;
        case ITEM_TOGGLE_THEME:
            mvprintw(item.y, item.x, "**");
            mvprintw(item.y + 1, item.x, "**");
            break;
    }
}
