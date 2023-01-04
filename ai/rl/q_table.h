#pragma once

#include <stdlib.h>
#include "containers/coord.h"
#include "maze.h"

#define Q_MIN (-800)

typedef double reward_t;

typedef direction_t action_t;

typedef struct {
    coord_t coord;
    unsigned depth;
} state_t;


typedef struct {
    size_t nx, ny, nd, na;
    double lr, gamma;
    reward_t *table;
    maze_state_t *environment;
} q_table_t;

q_table_t *
q_table_create(size_t nx, size_t ny, size_t nd, size_t na, double lr, double gamma, maze_state_t *environment);

reward_t q_value_get(q_table_t *table, state_t state, action_t action);

reward_t q_value_max(q_table_t *table, state_t state);

action_t q_action_max(q_table_t *table, state_t state);

void q_value_set(q_table_t *table, state_t state, action_t action, reward_t q_value);

void q_update(q_table_t *table, state_t state, state_t n_state, action_t action, reward_t reward);

void q_print(q_table_t *table);
