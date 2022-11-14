#include "solver.h"

path_values_t solve(maze_state_t *maze) {
    path_values_t best;
    int best_score = INT_MIN;

    int max_bonus = 0;
    for (int r = 0; r < maze->matrix->rows; ++r)
        for (int c = 0; c < maze->matrix->cols; ++c)
            if (maze_get(maze, c(c, r))) max_bonus++;

    matrix_t *cache = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MIN);

    heap_t *heap = heap_create(1000);

    heap_insert(heap, 0, maze_copy(maze));
    matrix_set(cache, cx(maze->pos), 0);

    while (!heap_empty(heap)) {
        maze_state_t *state = heap_extract(heap);
        int score = maze_score(state);

        if (maze_is_end(state)) {
            if (score > best_score) {
                best = path_values(state->path);
                best_score = score;
            }
            if (state->coins == max_bonus || !can_outperform(best_score, max_bonus, state)) break;

            maze_free(state);

            continue;
        }

        for (int i = 0; i < 4; ++i) {
            coord_t n_pos = c_add(state->pos, movements[i]);

            if (!maze_can_go(state, n_pos) || matrix_get(cache, cx(n_pos)) >= score) continue;

            maze_state_t *n_state = maze_copy_move(state, i);

            matrix_set(cache, cx(n_pos), score);

            heap_insert(heap, maze_score(n_state), n_state);
        }

        maze_free(state);
    }

    return best;
}

bool can_outperform(int best_score, int max_bonus, maze_state_t *maze) {
    return best_score < maze_score(maze) + (max_bonus - maze->coins) * 10;
}
