#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *m;
    int rows, cols;
} maze_t;

typedef struct {
    int score, steps;
    char *path;
} maze_score_t;

void resize_maze(maze_t *maze, int x, int y);

char mget(maze_t *maze, int x, int y);
void mset(maze_t *maze, int x, int y, char v);

void load(char *path, maze_t *maze);