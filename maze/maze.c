#include "maze.h"

const coord_t movements[] = {c(1, 0), c(0, -1), c(-1, 0), c(0, 1)};

const char movement_to_char[] = {'E', 'N', 'W', 'S'};

maze_state_t *maze_create(int cols, int rows) {
    maze_state_t *maze = malloc(sizeof(maze_state_t));
    maze->matrix = matrix_create(cols, rows, ' ');
    maze->pos = maze->end = c(0, 0);
    maze->coins = maze->steps = maze->drills = 0;
    maze->lives = MAX_LIVES;
    maze->path = path_create();
    return maze;
}

void maze_destroy(maze_state_t *maze) {
    matrix_free(maze->matrix);
    path_free(maze->path);
}

void maze_free(maze_state_t *maze) {
    maze_destroy(maze);
    free(maze);
}

maze_state_t *maze_copy(maze_state_t *maze) {
    maze_state_t *n_maze = malloc(sizeof(maze_state_t));
    memcpy(n_maze, maze, sizeof(maze_state_t));
    n_maze->matrix = matrix_copy(maze->matrix);
    return n_maze;
}

maze_state_t *maze_copy_initial(maze_state_t *maze) {
    maze_state_t *n_maze = malloc(sizeof(maze_state_t));
    memcpy(n_maze, maze, sizeof(maze_state_t));
    n_maze->matrix = matrix_copy(maze->initial_matrix);
    n_maze->pos = n_maze->start;
    n_maze->coins = n_maze->steps = n_maze->drills = 0;
    n_maze->lives = MAX_LIVES;
    n_maze->path = NULL;
    return n_maze;
}

void maze_move(maze_state_t *maze, direction_t direction) {
    coord_t n_coord = c_add(maze->pos, movements[direction]);
    if (maze_can_go(maze, n_coord)) {
        maze->pos = n_coord;
        maze->steps += 1;
        maze->path = path_add(maze->path, direction);
        char ch = maze_get(maze, n_coord);
        if (ch == '$') maze->coins += 1;
        if (ch == '!') maze->coins /= 2;
        if (ch == 'T') maze->drills += 3;
        if (ch == '#') maze->drills -= 1;
        maze_set(maze, n_coord, ' ');
    }
}

maze_state_t *maze_copy_move(maze_state_t *maze, direction_t direction) {
    maze_state_t *n_maze = maze_copy(maze);
    maze_move(n_maze, direction);
    return n_maze;
}

char maze_get(maze_state_t *maze, coord_t coord) {
    return (char) matrix_get(maze->matrix, cx(coord));
}

void maze_set(maze_state_t *maze, coord_t coord, char v) {
    matrix_set(maze->matrix, cx(coord), v);
}

maze_state_t *maze_load_file(char *path) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("File not found!\n");
        exit(EXIT_FAILURE);
    }

    int cols, rows;
    fscanf(fp, "%d %d\n", &cols, &rows); // NOLINT(cert-err34-c)
    maze_state_t *maze = maze_create(cols, rows);

    for (int r = 0; r < rows; ++r) {
        getline(&line, &len, fp);
        for (int c = 0; c < cols; ++c) {
            if (line[c] == 'o') {
                maze->pos = c(c, r);
                maze->start = c(c, r);
                line[c] = ' ';
            }
            if (line[c] == '_') {
                maze->end = c(c, r);
            }
            maze_set(maze, c(c, r), line[c]);
        }
    }

    fclose(fp);
    if (line) free(line);
    maze->initial_matrix = matrix_copy(maze->matrix);
    return maze;
}

maze_state_t *maze_load_stdin() {
    char *line = NULL;
    size_t len = 0;

    int cols, rows;
    scanf("%d %d\n", &cols, &rows); // NOLINT(cert-err34-c)
    maze_state_t *maze = maze_create(cols, rows);

    for (int r = 0; r < rows; ++r) {
        getline(&line, &len, stdin);
        for (int c = 0; c < cols; ++c) {
            if (line[c] == 'o') {
                maze->pos = c(c, r);
                maze->start = c(c, r);
                line[c] = ' ';
            }
            if (line[c] == '_') {
                maze->end = c(c, r);
            }
            maze_set(maze, c(c, r), line[c]);
        }
    }

    if (line) free(line);
    maze->initial_matrix = matrix_copy(maze->matrix);
    return maze;
}

bool maze_is_end(maze_state_t *maze) {
    return c_eq(maze->pos, maze->end);
}

bool maze_valid_coord(maze_state_t *maze, coord_t coord) {
    return coord.x >= 0 && coord.x < maze->matrix->cols && coord.y >= 0 && coord.y < maze->matrix->rows;
}

bool maze_can_go(maze_state_t *maze, coord_t coord) {
    return maze_valid_coord(maze, coord) && (maze->drills > 0 || maze_get(maze, coord) != '#');
}

int maze_score(maze_state_t *maze) {
    return maze->coins * 10 - maze->steps;
}


void maze_rollback(maze_state_t *maze, int steps) {
    if(maze->lives == 0) return;

    path_values_t path = path_values(maze->path);
    path.size -= steps;
    maze_state_t *copy = maze_copy_initial(maze);
    maze_state_t *result = maze_simulate(copy, path);
    maze_free(copy);
    result->lives = maze->lives - 1;
    *maze = *result;
}

maze_state_t *maze_simulate(maze_state_t *maze, path_values_t path) {
    maze_state_t *copy = maze_copy(maze);
    for (int i = 0; i < (int) path.size; ++i) {
        maze_move(copy, path.values[i]);
    }
    return copy;
}


