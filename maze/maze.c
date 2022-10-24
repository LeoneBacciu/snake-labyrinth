#include "maze.h"


void resize_maze(maze_t *maze, int x, int y) {
    maze->cols = x;
    maze->rows = y;
    maze->m = malloc(sizeof(char) * y * x);
}

char mget(maze_t *maze, int x, int y) {
    return maze->m[y * (maze->cols) + x];
}

void mset(maze_t *maze, int x, int y, char v) {
    maze->m[y * (maze->cols) + x] = v;
}

void load(char *path, maze_t *maze) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int x, y;
    fscanf(fp, "%d %d\n", &x, &y);
    resize_maze(maze, x, y);

    for (int r = 0; r < y; ++r) {
        getline(&line, &len, fp);
        for (int c = 0; c < x; ++c) {
            mset(maze, c, r, line[c]);
        }
    }

    fclose(fp);
    if (line) free(line);
}
