/**
 * @file q_table.h
 * @brief Q-Table implementation
 * @author Leone Bacciu
 */

#pragma once

#include <stdlib.h>
#include "containers/coord.h"
#include "maze.h"

#define Q_MIN (-800) ///< @brief Min value of Q-Table cell

typedef double reward_t; ///< @brief Type of Q-Table reward

typedef direction_t action_t; ///< @brief Type of Q-Table action

/**
 * @struct state_t
 * @brief State of the Q-Table
 *
 * @var state_t::coord
 *  Position of player
 * @var state_t::depth
 *  Number of times this cell was already visited
 */
typedef struct {
    coord_t coord;
    unsigned depth;
} state_t;

/**
 * @struct q_table_t
 * @brief Q-Table
 *
 * @var q_table_t::nx
 *  Number of cols
 * @var q_table_t::ny
 *  Number of rows
 * @var q_table_t::nd
 *  Number of depth levels
 * @var q_table_t::na
 *  Number of actions
 * @var q_table_t::lr
 *  Learning rate
 * @var q_table_t::gamma
 *  Momentum
 * @var q_table_t::table
 *  Table stored as an array
 *  @attention Do not use directly
 *  @see q_value_get
 *  @see q_value_max
 *  @see q_value_set
 * @var q_table_t::environment
 *  The current maze state
 */
typedef struct {
    size_t nx, ny, nd, na;
    double lr, gamma;
    reward_t *table;
    maze_state_t *environment;
} q_table_t;

/**
 * @brief Create a Q-Table with the respective parameters
 * @param nx
 * @param ny
 * @param nd
 * @param na
 * @param lr
 * @param gamma
 * @param environment
 * @return pointer to the Q-Table
 */
q_table_t *
q_table_create(size_t nx, size_t ny, size_t nd, size_t na, double lr, double gamma, maze_state_t *environment);

/**
 * @brief Gets the reward in for the state-action pair
 * @param table
 * @param state
 * @param action
 * @return the corresponding learned reward
 */
reward_t q_value_get(q_table_t *table, state_t state, action_t action);

/**
 * @brief Gets the maximum reward obtainable from the current state
 * @param table
 * @param state
 * @return the max learned reward between all the possible actions
 */
reward_t q_value_max(q_table_t *table, state_t state);

/**
 * @brief Gets the action that gives the maximum reward from the current state
 * @param table
 * @param state
 * @return the action
 */
action_t q_action_max(q_table_t *table, state_t state);

/**
 * @brief Sets the reward for the state-action pair
 * @param table
 * @param state
 * @param action
 * @param reward
 */
void q_value_set(q_table_t *table, state_t state, action_t action, reward_t reward);

/**
 * @brief Updates the learned reward of the state-action pair, using the learning rate and the momentum
 * @param table
 * @param state previous state
 * @param n_state next state
 * @param action
 * @param reward
 */
void q_update(q_table_t *table, state_t state, state_t n_state, action_t action, reward_t reward);
