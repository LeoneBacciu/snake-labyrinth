#pragma once

#include <stdbool.h>
#include "maze/maze.h"
#include "rogueutil.h"
#define NOCOLOR (-1)

void char_to_move(maze_t *maze, int c);

void render_init();
void render_destroy();

void render_loop(int argc, char **argv);

void render_maze(maze_t *maze);
