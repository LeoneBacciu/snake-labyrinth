#include "agent.h"
#include "q_table.h"

int rand_less(int max) {
    return rand() % max;
}

bool fix_action(maze_state_t *maze, state_t state, action_t *action) {
    for (int i = 0; i < 4; ++i) {
        if (maze_can_go(maze, c_add(state.coord, movements[(*action + i) % 4]))) {
            *action = (*action + i) % 4;
            return true;
        }
    }
    return false;
}

void solve_rl(maze_state_t *maze) {
    double eps = 0.1;
    int max_path_depth = maze->matrix->cols * maze->matrix->rows;
    int episodes = 10000000;
    int max_depth = 4;

    q_table_t *table = q_table_create(maze->matrix->cols, maze->matrix->rows, max_depth, 4, 0.1, 0.9, maze);

    for (int i = 0; i < max_depth; ++i) {
        state_t state1 = {maze->end, i};
        for (int j = 0; j < 4; ++j) {
            q_value_set(table, state1, j, 0);
        }
    }

    for (int e = 0; e < episodes; ++e) {
        if (eps < 0.8 && e % (episodes / 5) == 0) eps += 0.1;

        coord_t pos;
        do {
            pos = c(rand_less(maze->matrix->cols), rand_less(maze->matrix->rows));
        } while (!maze_can_go(maze, pos) || c_eq(pos, maze->end));

        state_t state = {pos, 0};

        matrix_t *visited = matrix_create(maze->matrix->cols, maze->matrix->rows, -1);

        for (int i = 0; i < max_path_depth; ++i) {
            action_t action;
            if (((double) rand()) / RAND_MAX > eps) { // explore
                action = rand_less(4);
            } else { // exploit
                action = q_action_max(table, state);
            }

            bool ok = fix_action(maze, state, &action);
            if (!ok) break;

            coord_t n_pos = c_add(state.coord, movements[action]);
            unsigned n_depth = matrix_get(visited, cx(state.coord)) + 1;
            state_t n_state = {n_pos, n_depth};
            reward_t reward = s_value(table, n_state);
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
    q_print(table);


    matrix_t *visited = matrix_create(maze->matrix->cols, maze->matrix->rows, 0);
    state_t st = {maze->pos, 0};
    while (!c_eq(st.coord, maze->end)) {
        maze_set(maze, st.coord, 'x');
        action_t action = q_action_max(table, st);
        st.coord = c_add(st.coord, movements[action]);
        st.depth = matrix_get(visited, cx(st.coord));
        matrix_set(visited, cx(st.coord), st.depth + 1);
        if (st.depth > max_depth - 1) break;
    }
    printf("\n");
    printf("\n");
    for (int yy = 0; yy < maze->matrix->rows; ++yy) {
        for (int xx = 0; xx < maze->matrix->cols; ++xx) {
            printf("%c", maze_get(maze, c(xx, yy)));
        }
        printf("\n");
    }
}
