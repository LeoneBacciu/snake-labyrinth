#include "maze.h"

maze_t *maze_make() {
    maze_t *maze;
    maze = malloc(sizeof(maze_t));
    return maze;
}

void maze_destroy(maze_t *maze) {
    free(maze);
}

void maze_move(maze_t *maze, int dx, int dy) {
    maze->pos.x = clamp(0, maze->pos.x + dx, maze->cols - 1);
    maze->pos.y = clamp(0, maze->pos.y + dy, maze->rows - 1);
}

void maze_resize(maze_t *maze, int x, int y) {
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
    maze_resize(maze, x, y);

    for (int r = 0; r < y; ++r) {
        getline(&line, &len, fp);
        for (int c = 0; c < x; ++c) {
            if (line[c] == 'o') {
                maze->pos.x = c;
                maze->pos.y = r;
                line[c] = ' ';
            }
            if (line[c] == '_') {
                maze->end.x = c;
                maze->end.y = r;
            }
            mset(maze, c, r, line[c]);
        }
    }

    fclose(fp);
    if (line) free(line);
}
