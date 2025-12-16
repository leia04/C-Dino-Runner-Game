#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "render.h"
#include "game.h"
#include "score.h"
#include "ui.h"

int main(void) {
    initscr();
    init_colors();
    noecho();
    curs_set(FALSE);
    timeout(-1);
    keypad(stdscr, TRUE);
    srand((unsigned)time(NULL));

    Player player;
    int scores[100];
    int try_count = 0;

    get_player_name(&player);
    Character selected_character = select_character(player.character_name);

    int high_score = read_high_score();

    timeout(0);

    Position dino = {5, GROUND_Y};
    Position obstacles[MAX_OBSTACLES];
    Position clouds[MAX_CLOUDS];
    Position item = {-1, -1};
    int item_type = 0;

    int score = 0, game_over = 0, initial_run = 1;
    int jumping = 0, jump_counter = 0;
    int delay = INITIAL_DELAY;
    int max_obstacles = INITIAL_OBSTACLES;
    int last_speed_increase = 0, last_obstacle_increase = 0;
    int crouching = 0, crouch_counter = 0;
    int item_active = 0, reverse_controls = 0, theme = 0;
    int score_saved = 0, paused = 0;

    reset_game(&dino, obstacles, clouds, &score, &game_over, &initial_run, &jumping, &jump_counter,
               &delay, &max_obstacles, &last_speed_increase, &last_obstacle_increase,
               &crouching, &crouch_counter, &item, &item_active, &reverse_controls, &theme);

    while (1) {
        if (!paused) {
            clear();

            for (int i = 0; i < MAX_CLOUDS; i++) {
                if (!game_over) {
                    if (theme == 0) draw_cloud(clouds[i]);
                    else draw_star(clouds[i]);
                    clouds[i].x--;
                    if (clouds[i].x < 0) {
                        clouds[i].x = COLS;
                        clouds[i].y = rand() % (GROUND_Y / 2);
                    }
                } else {
                    if (theme == 0) draw_cloud(clouds[i]);
                    else draw_star(clouds[i]);
                }
            }

            if (theme == 0) draw_sun();
            else draw_moon();

            for (int x = 0; x < COLS; x++) mvprintw(GROUND_Y + DINO_HEIGHT, x, "-");

            if (!game_over) {
                if (jumping) {
                    if (jump_counter < JUMP_DELAY) dino.y--;
                    else if (jump_counter < 2 * JUMP_DELAY) dino.y++;
                    else { jumping = 0; jump_counter = 0; dino.y = GROUND_Y; }
                    jump_counter++;
                }

                if (crouching) {
                    if (crouch_counter < CROUCH_DURATION) crouch_counter++;
                    else { crouching = 0; crouch_counter = 0; }
                }

                draw_dino(dino, crouching, selected_character);

                for (int i = 0; i < max_obstacles; i++) {
                    draw_obstacle(obstacles[i]);
                    obstacles[i].x--;
                    if (obstacles[i].x + OBSTACLE_WIDTH < 0) {
                        generate_obstacle(&obstacles[i], obstacles[(i - 1 + max_obstacles) % max_obstacles].x);
                        if (obstacles[i].x < COLS) obstacles[i].x = COLS;
                        if (!initial_run) score += 50;
                    }

                    if (check_collision(dino, obstacles[i], crouching)) {
                        game_over = 1;
                        player.score = score;
                        player.is_restart = 0;
                        player.time = time(NULL);
                        if (!score_saved) {
                            save_score(player);
                            scores[try_count++] = score;
                            score_saved = 1;
                        }
                    }
                }

                if (!item_active && (rand() % 500) == 0) {
                    item_active = 1;
                    item.x = COLS;
                    item.y = GROUND_Y - 5;
                    item_type = (rand() % 3) + 1;
                }

                if (item_active) {
                    draw_item(item, item_type);
                    item.x--;
                    if (check_item_collision(dino, item)) {
                        apply_item_effect(item_type, &delay, &reverse_controls, &theme);
                        item_active = 0;
                        item.x = -1; item.y = -1;
                    } else if (item.x < 0) item_active = 0;
                }

                if (obstacles[0].x + OBSTACLE_WIDTH == COLS - 1) initial_run = 0;

                if (score >= last_speed_increase + SPEED_INCREASE_INTERVAL) {
                    delay -= SPEED_INCREASE_AMOUNT;
                    if (delay < MIN_DELAY) delay = MIN_DELAY;
                    last_speed_increase = score;
                }

                if (score >= last_obstacle_increase + OBSTACLE_INCREASE_INTERVAL) {
                    if (max_obstacles < MAX_OBSTACLES) {
                        obstacles[max_obstacles].x = COLS + MIN_OBSTACLE_DISTANCE;
                        obstacles[max_obstacles].y = GROUND_Y - (rand() % (GROUND_Y - OBSTACLE_MAX_HEIGHT + 1));
                        max_obstacles++;
                    }
                    last_obstacle_increase = score;
                }

                mvprintw(0, 0, "Score: %d  High Score: %d", score, high_score);
            } else {
                mvprintw(LINES / 2,     COLS / 2 - 5,  "Game Over!");
                mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Press 'r' to try again.");
                mvprintw(LINES / 2 + 2, COLS / 2 - 10, "Press 'q' to exit the game.");
            }

            int ch = getch();

            if (ch == 'q') {
                player.score = score;
                player.is_restart = 0;
                player.time = time(NULL);
                if (!score_saved) save_score(player);
                break;
            }

            if ((!reverse_controls && (ch == ' ' || ch == KEY_UP)) || (reverse_controls && ch == KEY_DOWN)) {
                if (!jumping && !game_over) { jumping = 1; crouching = 0; crouch_counter = 0; }
            }

            if ((!reverse_controls && ch == KEY_DOWN) || (reverse_controls && (ch == ' ' || ch == KEY_UP))) {
                if (!jumping && !game_over) { crouching = 1; crouch_counter = 0; }
            }

            if (ch == 'r' && game_over) {
                player.score = score;
                player.is_restart = 1;
                player.time = time(NULL);
                reset_game(&dino, obstacles, clouds, &score, &game_over, &initial_run, &jumping, &jump_counter,
                           &delay, &max_obstacles, &last_speed_increase, &last_obstacle_increase,
                           &crouching, &crouch_counter, &item, &item_active, &reverse_controls, &theme);
                score_saved = 0;
            }

            if (ch == 'p' && !game_over) {
                paused = 1;
                clear();
                mvprintw(LINES / 2,     COLS / 2 - 5,  "Game Paused");
                mvprintw(LINES / 2 + 1, COLS / 2 - 10, "Press 'p' to resume.");
                refresh();
            }

            refresh();
            if (!game_over) { usleep(delay); score++; }
        } else {
            int ch = getch();
            if (ch == 'p') paused = 0;
        }
    }

    endwin();
    print_game_over(player, scores, try_count);
    return 0;
}
