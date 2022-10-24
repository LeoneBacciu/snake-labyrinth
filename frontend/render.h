#pragma once

#include <ncurses.h>
#include "maze/maze.h"

void render_init();
void render_destroy();

void render_loop(int argc, char **argv);

void render_maze(maze_t *maze, bool with_input);
