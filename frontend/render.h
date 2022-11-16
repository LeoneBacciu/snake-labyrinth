#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include "maze/maze.h"

attr_t char_to_color(char ch);

char char_to_display(char ch);

void char_to_move(maze_state_t *maze, int c);

void render_init();

void render_destroy();

void render_loop(int argc, char **argv);

void render_maze(maze_state_t *maze);

void render_end_game();

int render_menu(char *title, int choices_count, char **choices);