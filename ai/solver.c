#include "solver.h"
#include "random.h"

maze_state_t *solve(maze_state_t *maze) {
    maze_state_t *best = maze_copy(maze);
    int best_score = INT_MIN;

    int directions[] = {0, 1, 2, 3};

    int max_bonus = 0, max_drills = 0;
    for (int r = 0; r < maze->matrix->rows; ++r) {
        for (int c = 0; c < maze->matrix->cols; ++c) {
            if (maze_get(maze, c(c, r)) == '$') max_bonus += 10;
            if (maze_get(maze, c(c, r)) == 'T') max_drills += 3;
        }
    }

    matrix_t *highest = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MIN);
    matrix_t *shortest = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MAX);
    matrix_t *drillest = matrix_create(maze->matrix->cols, maze->matrix->rows, 0);

    heap_t *heap = heap_create(1000);

    heap_insert(heap, 0, maze_copy(maze));
    matrix_set(highest, cx(maze->pos), 0);

    while (!heap_empty(heap)) {
        maze_state_t *state = heap_extract(heap);
        int score = maze_score(state);

        if (maze_is_end(state)) {
            if (score > best_score) {
                best->path = path_copy(state->path);
                best_score = score;
            }
            if (state->coins == max_bonus &&
                state->drills == max_drills &&
                !can_outperform(best_score, max_bonus, state))
                break;

            maze_free(state);

            continue;
        }

        random_shuffle(directions, 4);
        for (int i = 0; i < 4; ++i) {
            int d = directions[i];
            coord_t n_pos = c_add(state->pos, movements[d]);

            if (!maze_can_go(state, n_pos) ||
                matrix_get(drillest, cx(n_pos)) >= state->drills &&
                matrix_get(shortest, cx(n_pos)) <= state->steps &&
                matrix_get(highest, cx(n_pos)) >= score)
                continue;

            maze_state_t *n_state = maze_copy_move(state, d);

            matrix_set_max(highest, cx(n_pos), score);
            matrix_set_min(shortest, cx(n_pos), state->steps);
            matrix_set_max(drillest, cx(n_pos), state->drills);

            heap_insert(heap, maze_score(n_state), n_state);
        }

        maze_free(state);
    }

    return best;
}

bool can_outperform(int best_score, int max_bonus, maze_state_t *maze) {
    return best_score < maze_score(maze) + (max_bonus - maze->coins) * 10;
}

/*ritorna il percorso migliore partendo da maze.pos, essendo stato nelle celle visited e
 * non impiegando più di depth passi */

typedef struct {

    path_t *path;
    int score;
} solution_t;


solution_t ciccioricorsione(maze_state_t *maze, matrix_t *visited, int depth) {

    if (depth == 0) {
        return (solution_t) {NULL, INT_MIN};
    }
    coord_t init_pos = maze->pos;
    int init_coins = maze->coins;
    int init_steps = maze->steps;
    int init_drills = maze->drills;


    for (int i = 0; i < 4; ++i) {

    }
}

maze_state_t *solve_rec(maze_state_t *maze) {


}