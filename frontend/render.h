#pragma once

#define _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include "maze/maze.h"
#include <ncurses.h>

#ifdef USE_MENU
#include <menu.h>
#endif

#define IS_VERTEX(c, r, ratio) (((r % ratio == 0) + (c % ratio == 0) + (r % ratio == ratio - 1) + (c % ratio == ratio - 1)) == 2)

typedef struct {
    bool b[4];
} borders_t;

void char_to_move(maze_state_t *maze, int c);

void render_init();

void render_destroy();

void render_loop(int argc, char **argv);

void render_maze(maze_state_t *maze);

void render_end_game(maze_state_t *maze);

#ifdef USE_MENU
int render_menu(char *title, int choices_count, char **choices);
#endif

void render_replay(maze_state_t *maze);
