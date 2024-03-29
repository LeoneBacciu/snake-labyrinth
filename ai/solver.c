/**
 * @file solver.c
 */

#include "solver.h"
#include "random.h"

/**
 * @internal
 * @brief Executes one run of the fast solver
 * @param maze
 * @return the solved maze
 */
static maze_state_t *solve_fast_internal(maze_state_t *maze) {
    maze_state_t *best = maze_copy(maze);
    int best_score = INT_MIN;

    int directions[] = {0, 1, 2, 3};

    int max_coins = 0, max_drills = 0;
    for (int r = 0; r < maze->matrix->rows; ++r) {
        for (int c = 0; c < maze->matrix->cols; ++c) {
            if (maze_get(maze, c(c, r)) == '$') max_coins += 1;
            if (maze_get(maze, c(c, r)) == 'T') max_drills += 3;
        }
    }

    matrix_t *highest = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MIN);
    matrix_t *shortest = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MAX);
    matrix_t *drillest = matrix_create(maze->matrix->cols, maze->matrix->rows, 0);

    heap_t *heap = heap_create(1000);

    heap_insert(heap, 0, maze_copy(maze));
    matrix_set(highest, cx(maze->head), 0);
    matrix_set(shortest, cx(maze->head), 0);
    matrix_set(drillest, cx(maze->head), 0);

    while (!heap_empty(heap)) {
        maze_state_t *state = heap_extract(heap);
        int score = maze_score(state);

        if (maze_is_end(state)) {
            if (score > best_score) {
                best->path = path_assign(state->path);
                best_score = score;
            }
            if (state->coins == max_coins &&
                state->drills == max_drills &&
                best_score > maze_score(state))
                break;

            maze_free(state);

            continue;
        }

        random_shuffle(directions, 4);
        for (int i = 0; i < 4; ++i) {
            int d = directions[i];
            coord_t n_pos = c_add(state->head, movements[d]);

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

    heap_free(heap);

    return maze_simulate(best, path_values(best->path));
}

maze_state_t *solve_fast(maze_state_t *maze) {
    maze_state_t *best = solve_fast_internal(maze);
    for (int i = 0; i < SOLVER_FAST_RUNS; ++i) {
        maze_state_t *tmp = solve_fast_internal(maze);
        if (maze_score(best) < maze_score(tmp)) {
            maze_free(best);
            best = tmp;
        } else {
            maze_free(tmp);
        }
    }
    return best;
}

/**
 * @internal
 * @struct solution_t
 * @brief Represents a candidate solution
 *
 * @var solution_t::score
 *  Score of the solution
 * @var solution_t::path
 *  Path of the solution
 */
typedef struct {
    int score;
    path_t *path;
} solution_t;

/**
 * @internal
 * @brief Complete search for a solution
 * @param maze
 * @param visited matrix of visited cells
 * @param depth max depth of solution
 * @return the best solution_t
 */
static solution_t solve_strong_internal(maze_state_t *maze, matrix_t *visited, int depth) {
    if (depth == 0) return (solution_t) {INT_MIN, path_create()};

    if (maze_is_end(maze)) return (solution_t) {maze_score(maze), path_assign(maze->path)};

    solution_t final = {INT_MIN, path_create()};


    for (direction_t direction = 0; direction < 4; ++direction) {
        coord_t n_pos = c_add(maze->head, movements[direction]);
        maze_state_t *copy = maze_copy_move(maze, direction);

        int prev_score = matrix_get(visited, cx(n_pos));

        if (!maze_can_go(maze, n_pos) || prev_score > maze_score(maze)) continue;


        matrix_set(visited, cx(n_pos), maze_score(maze));


        solution_t tmp = solve_strong_internal(copy, visited, depth - 1);
        maze_free(copy);
        if (tmp.score > final.score) final = tmp;


        matrix_set(visited, cx(n_pos), prev_score);
    }
    return final;
}

maze_state_t *solve_strong(maze_state_t *maze) {
    matrix_t *visited = matrix_create(maze->matrix->cols, maze->matrix->rows, INT_MIN);
    solution_t solution = solve_strong_internal(maze, visited, SOLVER_STRONG_DEPTH);
    return maze_simulate(maze, path_values(solution.path));
}