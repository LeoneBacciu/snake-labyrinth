/**
 * @file q_table.c
 * @author Leone Bacciu
 */

#include "q_table.h"

/**
 * @internal
 * @brief Calculates the index for the state-action pair
 * @param table
 * @param state
 * @param action
 * @return the index in the table array
 */
static size_t q_table_index(q_table_t *table, state_t state, action_t action) {
    size_t py = state.coord.y * table->nx * table->nd * table->na;
    size_t px = state.coord.x * table->nd * table->na;
    size_t pd = state.depth * table->na;
    size_t pa = action;
    return py + px + pd + pa;
}

q_table_t *
q_table_create(size_t nx, size_t ny, size_t nd, size_t na, double lr, double gamma, maze_state_t *environment) {
    q_table_t *q_table = malloc(sizeof(q_table_t));
    q_table->nx = nx;
    q_table->ny = ny;
    q_table->nd = nd;
    q_table->na = na;
    q_table->lr = lr;
    q_table->gamma = gamma;
    q_table->table = calloc(nx * ny * nd * na, sizeof(reward_t));
    for (int i = 0; i < nx * ny * nd * na; ++i) {
        q_table->table[i] = Q_MIN;
    }
    q_table->environment = environment;
    return q_table;
}

reward_t q_value_get(q_table_t *table, state_t state, action_t action) {
    return table->table[q_table_index(table, state, action)];
}

reward_t q_value_max(q_table_t *table, state_t state) {
    reward_t mx = Q_MIN;
    for (action_t action = 0; action < 4; ++action) {
        reward_t reward = table->table[q_table_index(table, state, action)];
        if (mx < reward) mx = reward;
    }
    return mx;
}

action_t q_action_max(q_table_t *table, state_t state) {
    action_t mxa = LEFT;
    reward_t mx = Q_MIN;
    for (action_t action = 0; action < 4; ++action) {
        reward_t reward = table->table[q_table_index(table, state, action)];
        if (mx < reward) {
            mx = reward;
            mxa = action;
        }
    }
    return mxa;
}

void q_value_set(q_table_t *table, state_t state, action_t action, reward_t reward) {
    table->table[q_table_index(table, state, action)] = MAX(Q_MIN, reward);
}

void q_update(q_table_t *table, state_t state, state_t n_state, action_t action, reward_t reward) {
    reward_t left = q_value_get(table, state, action);

    reward_t q_max = q_value_max(table, n_state);

    reward_t right = (reward + table->gamma * q_max);

    q_value_set(table, state, action, (1 - table->lr) * left + (table->lr) * right);
}
