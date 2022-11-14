#include "maze.h"

maze_t *maze_create() {
    maze_t *maze;
    maze = malloc(sizeof(maze_t));
    return maze;
}

void maze_destroy(maze_t *maze) {
    free(maze);
}

void maze_move(maze_t *maze, coord_t coord) {
    coord_t n_coord = c_add(maze->pos, coord);
    if (maze_can_go(maze, n_coord)) {
        maze->pos = n_coord;
        char c = mget(maze, n_coord);
        if (c == '$' || c == '!') mset(maze, n_coord, ' ');
    }
}

void maze_resize(maze_t *maze, int cols, int rows) {
    free(maze->_m);
    maze->cols = cols;
    maze->rows = rows;
    maze->_m = malloc(sizeof(char) * rows * cols);
}

char mget(maze_t *maze, coord_t coord) {
    return maze->_m[coord.y * (maze->cols) + coord.x];
}

void mset(maze_t *maze, coord_t coord, char v) {
    maze->_m[coord.y * (maze->cols) + coord.x] = v;
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
            mset(maze, c(c, r), line[c]);
        }
    }

    fclose(fp);
    if (line) free(line);
}

bool maze_is_end(maze_t *maze) {
    return c_eq(maze->pos, maze->end);
}

bool maze_valid_coord(maze_t *maze, coord_t coord) {
    return coord.x >= 0 && coord.x < maze->cols && coord.y >= 0 && coord.y < maze->rows;
}

bool maze_can_go(maze_t *maze, coord_t coord) {
    return maze_valid_coord(maze, coord) && mget(maze, coord) != '#';
}