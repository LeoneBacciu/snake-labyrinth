#pragma once

#define _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include "maze/maze.h"
#include <ncurses.h>
#include <menu.h>

typedef struct {
    bool b[4];
} borders_t;

void char_to_move(maze_state_t *maze, int c);

void render_init();

void render_destroy();

void render_loop(int argc, char **argv);

void render_maze(maze_state_t *maze);

void render_end_game(maze_state_t *maze);

int render_menu(char *title, int choices_count, char **choices);

void render_replay(maze_state_t *maze);
