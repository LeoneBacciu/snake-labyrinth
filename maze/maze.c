#include "maze.h"

maze_t *maze_create() {
    maze_t *maze;
    maze = malloc(sizeof(maze_t));
    return maze;
}

void maze_destroy(maze_t *maze) {
    free(maze);
}

void maze_move(maze_t *maze, int dx, int dy) {
    int nx = clamp(0, maze->pos.x + dx, maze->cols - 1);
    int ny = clamp(0, maze->pos.y + dy, maze->rows - 1);
    if (maze_can_go(maze, nx, ny)) {
        maze->pos.x = nx;
        maze->pos.y = ny;
    }
    char c = mget(maze, nx, ny);
    if (c == '$' || c == '!') mset(maze, nx, ny, ' ');
}

void maze_resize(maze_t *maze, int x, int y) {
    free(maze->_m);
    maze->cols = x;
    maze->rows = y;
    maze->_m = malloc(sizeof(char) * y * x);
}

char mget(maze_t *maze, int x, int y) {
    return maze->_m[y * (maze->cols) + x];
}

void mset(maze_t *maze, int x, int y, char v) {
    maze->_m[y * (maze->cols) + x] = v;
}

void maze_load(maze_t *maze, char *path) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("File not found!\n");
        exit(EXIT_FAILURE);
    }

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

bool maze_is_end(maze_t *maze) {
    return (maze->pos.x == maze->end.x) && (maze->pos.y == maze->end.y);
}

bool maze_can_go(maze_t *maze, int x, int y) {
    return (mget(maze, x, y) != '#');
}