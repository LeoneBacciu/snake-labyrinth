#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <stdbool.h>

typedef struct {
    int x, y;
} coord_t;

typedef struct {
    char *m;
    int rows, cols;
    coord_t pos, end;
} maze_t;

typedef struct {
    int score, steps;
    char *path;
} maze_score_t;

maze_t *maze_make();

void maze_destroy(maze_t *maze);

void maze_move(maze_t *maze, int dx, int dy);

void maze_resize(maze_t *maze, int x, int y);

char mget(maze_t *maze, int x, int y);

void mset(maze_t *maze, int x, int y, char v);

void load(char *path, maze_t *maze);

bool can_go(maze_t *maze, int x, int y);