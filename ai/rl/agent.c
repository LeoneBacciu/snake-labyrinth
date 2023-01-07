#include "agent.h"

/**
 * @internal
 * @brief Transform the action in a visitable one
 * @param maze
 * @param state
 * @param action
 * @return true if the action can be fixed, else false
 */
static bool fix_action(maze_state_t *maze, state_t state, action_t *action) {
    for (int i = 0; i < 4; ++i) {
        if (maze_can_go(maze, c_add(state.coord, movements[(*action + i) % 4]))) {
            *action = (*action + i) % 4;
            return true;
        }
    }
    return false;
}

maze_state_t *solve_rl(maze_state_t *maze) {
    double eps = 0.1;
    int max_path_depth = maze->matrix->cols * maze->matrix->rows * 10;
    int episodes = 1000000;
    int max_depth = 4;

    q_table_t *table = q_table_create(maze->matrix->cols, maze->matrix->rows, max_depth, 4, 0.1, 0.9, maze);

    for (int i = 0; i < max_depth; ++i) {
        state_t state1 = {maze->end, i};
        for (int j = 0; j < 4; ++j) {
            q_value_set(table, state1, j, 0);
        }
    }

    for (int e = 0; e < episodes; ++e) {
        maze = maze_copy_initial(maze);
        if (eps <= 0.8 && e % (episodes / 5) == 0) eps += 0.1;

        coord_t pos;
        do {
            pos = c(random_range_int(0, maze->matrix->cols - 1), random_range_int(0, maze->matrix->rows - 1));
        } while (!maze_can_go(maze, pos) || c_eq(pos, maze->end));

        state_t state = {pos, 0};

        matrix_t *visited = matrix_create(maze->matrix->cols, maze->matrix->rows, -1);

        for (int i = 0; i < max_path_depth; ++i) {
            action_t action;
            if (random_range_double(0, 1) > eps) { // explore
                action = random_range_int(0, 3);
            } else { // exploit
                action = q_action_max(table, state);
            }

            bool ok = fix_action(maze, state, &action);
            if (!ok) break;

            coord_t n_pos = c_add(state.coord, movements[action]);
            unsigned n_depth = matrix_get(visited, cx(state.coord)) + 1;
            state_t n_state = {n_pos, n_depth};

            int p_score = maze_score(maze);
            maze_move(maze, action);
            reward_t reward = maze_score(maze) - p_score;

            if (i >= max_path_depth - 1) reward = -100;
            if (i >= max_path_depth - 1) break;
            if (n_depth > max_depth - 1) reward = -100;
            q_update(table, state, n_state, action, reward);

            state = n_state;
            matrix_set(visited, cx(state.coord), state.depth);

            if (c_eq(state.coord, maze->end))
                break;
            if (state.depth > max_depth - 1) break;
        }

        matrix_free(visited);
    }

    matrix_t *visited = matrix_create(maze->matrix->cols, maze->matrix->rows, 0);
    state_t st = {maze->head, 0};
    path_t *best_path = path_create();
    while (!c_eq(st.coord, maze->end)) {
        action_t action = q_action_max(table, st);
        best_path = path_add(best_path, action);
        st.coord = c_add(st.coord, movements[action]);
        st.depth = matrix_get(visited, cx(st.coord));
        matrix_set(visited, cx(st.coord), st.depth + 1);
        if (st.depth > max_depth - 1) break;
    }
    return maze_simulate(maze, path_values(best_path));
}
